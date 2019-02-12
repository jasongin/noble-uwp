'use strict';

// Noble bindings for Windows UWP BLE APIs

const events = require('events');
const util = require('util');
const debug = require('debug')('noble-uwp');
const rt = require('./rt-utils');

// Note the load order here is important for cross-namespace dependencies.
rt.using('Windows.Foundation');
rt.using('Windows.Storage.Streams');
rt.using('Windows.Devices.Enumeration');
rt.using('Windows.Devices.Bluetooth.GenericAttributeProfile');
rt.using('Windows.Devices.Bluetooth');
rt.using('Windows.Devices.Bluetooth.Advertisement');
rt.using('Windows.Devices.Radios');

const BluetoothLEDevice = Windows.Devices.Bluetooth.BluetoothLEDevice;
const BluetoothCacheMode = Windows.Devices.Bluetooth.BluetoothCacheMode;
const BluetoothUuidHelper = Windows.Devices.Bluetooth.BluetoothUuidHelper;
const BluetoothConnectionStatus = Windows.Devices.Bluetooth.BluetoothConnectionStatus;

const BluetoothLEAdvertisementWatcher = Windows.Devices.Bluetooth.Advertisement.BluetoothLEAdvertisementWatcher;
const BluetoothLEScanningMode = Windows.Devices.Bluetooth.Advertisement.BluetoothLEScanningMode;
const BluetoothLEAdvertisementType = Windows.Devices.Bluetooth.Advertisement.BluetoothLEAdvertisementType;
const BluetoothLEAdvertisementDataTypes = Windows.Devices.Bluetooth.Advertisement.BluetoothLEAdvertisementDataTypes;
const BluetoothLEAdvertisementWatcherStatus =
		Windows.Devices.Bluetooth.Advertisement.BluetoothLEAdvertisementWatcherStatus;

const GattCharacteristicProperties = Windows.Devices.Bluetooth.GenericAttributeProfile.GattCharacteristicProperties;
const GattDeviceService = Windows.Devices.Bluetooth.GenericAttributeProfile.GattDeviceService;
const GattServiceUuids = Windows.Devices.Bluetooth.GenericAttributeProfile.GattServiceUuids;
const GattCommunicationStatus = Windows.Devices.Bluetooth.GenericAttributeProfile.GattCommunicationStatus;
const GattClientCharacteristicConfigurationDescriptorValue =
		Windows.Devices.Bluetooth.GenericAttributeProfile.GattClientCharacteristicConfigurationDescriptorValue;

const Radio = Windows.Devices.Radios.Radio;
const RadioKind = Windows.Devices.Radios.RadioKind;
const RadioState = Windows.Devices.Radios.RadioState;

const DataReader = Windows.Storage.Streams.DataReader;

let NobleBindings = function () {
	this._radio = null;
	this._radioState = 'unknown';
	this._deviceMap = {};
	this._devicesListeners = {};
	this._acceptOnlyScanResponse = false;
};

util.inherits(NobleBindings, events.EventEmitter);

NobleBindings.prototype.init = function () {
	this._onAdvertisementWatcherReceived = this._onAdvertisementWatcherReceived.bind(this);
	this._onAdvertisementWatcherStopped = this._onAdvertisementWatcherStopped.bind(this);
	this._onConnectionStatusChanged = this._onConnectionStatusChanged.bind(this);

	this._advertisementWatcher = new BluetoothLEAdvertisementWatcher();
	this._advertisementWatcher.scanningMode = BluetoothLEScanningMode.active;
	this._advertisementWatcher.on('received', this._onAdvertisementWatcherReceived);
	this._advertisementWatcher.on('stopped', this._onAdvertisementWatcherStopped);

	debug('initialized');

	rt.promisify(Radio.getRadiosAsync)().then(radiosList => {
		radiosList = rt.toArray(radiosList);
		this._radio = radiosList.find(radio => radio.kind === RadioKind.bluetooth);
		if (this._radio) {
			debug('found bluetooth radio: %s', this._radio.name);
			this._radio.on('stateChanged', (sender, e) => {
				this._updateRadioState();
			});
		} else {
			debug('no bluetooth radio found');
		}
		this._updateRadioState();
	}).catch(ex => {
		debug('failed to get radios: %s', ex.stack);
		this._updateRadioState();
	});
};

NobleBindings.prototype.startScanning = function (serviceUuids, allowDuplicates) {
	if (!(serviceUuids && serviceUuids.length > 0)) {
		serviceUuids = null;
	}
	allowDuplicates = !!allowDuplicates;

	debug('startScanning(%s, %s)', (serviceUuids ? serviceUuids.join() : ''), allowDuplicates);

	this._filterAdvertisementServiceUuids = serviceUuids;
	this._allowAdvertisementDuplicates = allowDuplicates;

	if (this._advertisementWatcher.status === BluetoothLEAdvertisementWatcherStatus.started) {
		return;
	}

	this._advertisementWatcher.start();
	rt.keepAlive(true);
}

NobleBindings.prototype.stopScanning = function () {
	if (this._advertisementWatcher.status === BluetoothLEAdvertisementWatcherStatus.started) {
		debug('stopScanning()');
		this._advertisementWatcher.stop();
		rt.keepAlive(false);
	}
};

NobleBindings.prototype.connect = function (deviceUuid) {
	debug('connect(%s)', deviceUuid);

	let deviceRecord = this._deviceMap[deviceUuid];
	if (!deviceRecord) {
		throw new Error('Invalid or unknown device UUID: ' + deviceUuid);
	}

	if (!deviceRecord.connectable) {
		throw new Error("Device is not connectable: " + deviceRecord.formattedAddress);
	}

	rt.promisify(BluetoothLEDevice.fromBluetoothAddressAsync)(deviceRecord.address).then(device => {
		if (device) {
			debug('got bluetooth device: %s (%s)', device.name, device.deviceInformation.kind);
			deviceRecord.device = rt.trackDisposable(deviceUuid, device);

			deviceRecord.device.on(
				'connectionStatusChanged', this._onConnectionStatusChanged);

			this.emit('connect', deviceUuid, null);
			rt.keepAlive(true);
		} else {
			this.emit('connect', deviceUuid, new Error('Failed to get a Bluetooth device pointer from address for device UUID: ' + deviceUuid));
		}
	}).catch(ex => {
		debug('failed to get device %s: %s', deviceRecord.formattedAddress, ex.stack);
		this.emit('connect', deviceUuid, ex);
	});
};

NobleBindings.prototype.disconnect = function (deviceUuid) {
	debug('disconnect(%s)', deviceUuid);

	let deviceRecord = this._deviceMap[deviceUuid];
	if (!deviceRecord) {
		throw new Error('Invalid or unknown device UUID: ' + deviceUuid);
	}

	if (deviceRecord.device) {
		deviceRecord.device.removeListener(
			'connectionStatusChanged', this._onConnectionStatusChanged);

		deviceRecord.device = null;
		deviceRecord.serviceMap = {};
		deviceRecord.characteristicMap = {};
		deviceRecord.descriptorMap = {};

		delete this._devicesListeners[deviceUuid];

		rt.disposeAll(deviceUuid);

		rt.keepAlive(false);
		this.emit('disconnect', deviceUuid);
	}
};

NobleBindings.prototype.updateRssi = function (deviceUuid) {
	debug('updateRssi(%s)', deviceUuid);

	// TODO: Retrieve updated RSSI
	let rssi = 0;

	this.emit('rssiUpdate', deviceUuid, rssi);
};

NobleBindings.prototype.discoverServices = function (deviceUuid, filterServiceUuids) {
	if (filterServiceUuids && filterServiceUuids.length === 0) {
		filterServiceUuids = null;
	}

	debug('discoverServices(%s, %s)', deviceUuid,
		(filterServiceUuids ? filterServiceUuids.join() : '(all)'));

	let deviceRecord = this._deviceMap[deviceUuid];
	if (!deviceRecord) {
		throw new Error('Invalid or unknown device UUID: ' + deviceUuid);
	}

	let device = deviceRecord.device;
	if (!device) {
		throw new Error('Device is not connected. UUID: ' + deviceUuid);
	}

	rt.promisify(device.getGattServicesAsync, device)(
		BluetoothCacheMode.uncached).then(result => {
			checkCommunicationResult(deviceUuid, result);

			let services = rt.trackDisposables(deviceUuid, rt.toArray(result.services));
			let serviceUuids = services.map(s => uuidToString(s.uuid))
				.filter(filterUuids(filterServiceUuids));

			debug(deviceUuid + ' services: %o', serviceUuids);
			this.emit('servicesDiscover', deviceUuid, serviceUuids);
		}).catch(ex => {
			debug('failed to get GATT services for device %s: %s', deviceUuid, ex.stack);
			this.emit('servicesDiscover', deviceUuid, ex);
		});
};

NobleBindings.prototype.discoverIncludedServices =
	function (deviceUuid, serviceUuid, filterServiceUuids) {
		if (filterServiceUuids && filterServiceUuids.length === 0) {
			filterServiceUuids = null;
		}

		debug('discoverIncludedServices(%s, %s, %s)', deviceUuid, serviceUuid,
			(filterServiceUuids ? filterServiceUuids.join() : '(all)'));

		this._getCachedServiceAsync(deviceUuid, serviceUuid).then(service => {
			rt.promisify(service.getIncludedServicesAsync, service)(
				BluetoothCacheMode.uncached).then(result => {
					checkCommunicationResult(deviceUuid, result);

					let includedServices = rt.trackDisposables(deviceUuid, rt.toArray(result.services));
					let includedServiceUuids = includedServices.map(s => uuidToString(s.uuid))
						.filter(filterUuids(filterServiceUuids));

					debug(deviceUuid + ' ' + serviceUuid + ' included services: ' + includedServiceUuids);
					this.emit('includedServicesDiscover', deviceUuid, serviceUuid, includedServiceUuids);
				});
		}).catch(ex => {
			debug('failed to get GATT included services for device %s: %s', deviceUuid, + ex.stack);
			this.emit('includedServicesDiscover', deviceUuid, serviceUuid, ex);
		});
	};

NobleBindings.prototype.discoverCharacteristics =
	function (deviceUuid, serviceUuid, filterCharacteristicUuids) {
		if (filterCharacteristicUuids && filterCharacteristicUuids.length === 0) {
			filterCharacteristicUuids = null;
		}

		debug('discoverCharacteristics(%s, %s, %s', deviceUuid, serviceUuid,
			(filterCharacteristicUuids ? filterCharacteristicUuids.join() : '(all)'));

		this._getCachedServiceAsync(deviceUuid, serviceUuid).then(service => {
			return rt.promisify(service.getCharacteristicsAsync, service)(
				BluetoothCacheMode.uncached).then(result => {
					checkCommunicationResult(deviceUuid, result);

					let characteristics = rt.toArray(result.characteristics)
						.filter(c => { return filterUuids(filterCharacteristicUuids)(uuidToString(c.uuid)); })
						.map(c => ({
							uuid: uuidToString(c.uuid),
							properties: characteristicPropertiesToStrings(c.characteristicProperties),
						}));

					debug('%s %s characteristics: %o', deviceUuid, serviceUuid,
						characteristics.map(c => c.uuid));
					this.emit('characteristicsDiscover', deviceUuid, serviceUuid, characteristics);
				});
		}).catch(ex => {
			debug('failed to get GATT characteristics for device %s: %s', deviceUuid, ex.stack);
			this.emit('characteristicsDiscover', deviceUuid, serviceUuid, ex);
		});
	};

NobleBindings.prototype.read = function (deviceUuid, serviceUuid, characteristicUuid) {
	debug('read(%s, %s, %s)', deviceUuid, serviceUuid, characteristicUuid);

	this._getCachedCharacteristicAsync(
			deviceUuid, serviceUuid, characteristicUuid).then(characteristic => {
		return rt.promisify(characteristic.readValueAsync, characteristic)(BluetoothCacheMode.uncached).then(result => {
			checkCommunicationResult(deviceUuid, result);
			let data = rt.toBuffer(result.value);

				debug('  => [' + data.length + ']');
				this.emit('read', deviceUuid, serviceUuid, characteristicUuid, data, false);
			});
		}).catch(ex => {
			debug('failed to read characteristic for device %s: %s', deviceUuid, ex.stack);
			this.emit('read', deviceUuid, serviceUuid, characteristicUuid, ex, false);
		});
};

NobleBindings.prototype.write =
	function (deviceUuid, serviceUuid, characteristicUuid, data, withoutResponse) {
		debug('write(%s, %s, %s, (data), %s)',
			deviceUuid, serviceUuid, characteristicUuid, withoutResponse);

		this._getCachedCharacteristicAsync(
			deviceUuid, serviceUuid, characteristicUuid).then(characteristic => {
				let rtBuffer = rt.fromBuffer(data);
				return rt.promisify(characteristic.writeValueWithResultAsync, characteristic)(
					rtBuffer).then(result => {
						checkCommunicationResult(deviceUuid, result);
						this.emit('write', deviceUuid, serviceUuid, characteristicUuid);
					});
			}).catch(ex => {
				debug('failed to write characteristic for device %s: %s', deviceUuid, ex.stack);
				if (!withoutResponse) {
					this.emit('write', deviceUuid, serviceUuid, characteristicUuid, ex);
				}
			});
	};

NobleBindings.prototype.broadcast =
	function (deviceUuid, serviceUuid, characteristicUuid, broadcast) {
		debug('broadcast(%s, %s, %s, %s)', deviceUuid, serviceUuid, + characteristicUuid, broadcast);

		this.emit('broadcast', deviceUuid, serviceUuid, characteristicUuid,
			new Error('Not implemented'));
	};

NobleBindings.prototype.notify = function (deviceUuid, serviceUuid, characteristicUuid, notify) {
	debug('notify(%s, %s, %s, %s)', deviceUuid, serviceUuid, characteristicUuid, notify);

	this._getCachedCharacteristicAsync(
		deviceUuid, serviceUuid, characteristicUuid).then(characteristic => {
			let listenerKey = serviceUuid + '/' + characteristicUuid;
			let deviceListeners = this._devicesListeners[deviceUuid] || {};
			let listener = deviceListeners[listenerKey];

			let descriptorValue = characteristic.characteristicProperties & GattCharacteristicProperties.indicate
				? GattClientCharacteristicConfigurationDescriptorValue.indicate
				: GattClientCharacteristicConfigurationDescriptorValue.notify;

			if (notify) {
				if (listener) {
					// Already listening.
					this.emit('notify', deviceUuid, serviceUuid, characteristicUuid, notify);
					return;
				}

				return rt.promisify(
					characteristic.writeClientCharacteristicConfigurationDescriptorWithResultAsync,
					characteristic)(descriptorValue)
					.then(result => {
						checkCommunicationResult(deviceUuid, result);

						listener = ((source, e) => {
							debug('notification: %s %s %s', deviceUuid, serviceUuid, characteristicUuid);
							let data = rt.toBuffer(e.characteristicValue);
							this.emit('read', deviceUuid, serviceUuid, characteristicUuid, data, true);
						}).bind(this);

						characteristic.addListener('valueChanged', listener);
						deviceListeners[listenerKey] = listener;
						this.emit('notify', deviceUuid, serviceUuid, characteristicUuid, notify);
					});
			} else {
				if (!listener) {
					// Already not listening.
					this.emit('notify', deviceUuid, serviceUuid, characteristicUuid, notify);
					return;
				}

				characteristic.removeListener('valueChanged', listener);
				delete deviceListeners[listenerKey];

				return rt.promisify(
					characteristic.writeClientCharacteristicConfigurationDescriptorWithResultAsync,
					characteristic)(GattClientCharacteristicConfigurationDescriptorValue.none)
					.then(result => {
						checkCommunicationResult(deviceUuid, result);

						this.emit('notify', deviceUuid, serviceUuid, characteristicUuid, notify);
					});
			}
		}).catch(ex => {
			debug('failed to enable characteristic notify for device %s: %s', deviceUuid, ex.stack);
			this.emit('notify', deviceUuid, serviceUuid, characteristicUuid, ex);
		});
};

NobleBindings.prototype.discoverDescriptors =
	function (deviceUuid, serviceUuid, characteristicUuid) {
		debug('discoverDescriptors(%s, %s, %s)', deviceUuid, serviceUuid, characteristicUuid);

		this._getCachedCharacteristicAsync(
			deviceUuid, serviceUuid, characteristicUuid).then(characteristic => {
				return rt.promisify(characteristic.getDescriptorsAsync, characteristic)(
					BluetoothCacheMode.uncached).then(result => {
						checkCommunicationResult(deviceUuid, result);

						let descriptors = rt.toArray(result.descriptors).map(d => uuidToString(d.uuid));
						this.emit('descriptorsDiscover', deviceUuid, serviceUuid, characteristicUuid, descriptors);
					});
			}).catch(ex => {
				debug('failed to get GATT characteristic descriptors for device %s: %s',
					deviceUuid, ex.stack);
				this.emit('descriptorsDiscover', deviceUuid, serviceUuid, characteristicUuid, ex);
			});
	};

NobleBindings.prototype.readValue =
	function (deviceUuid, serviceUuid, characteristicUuid, descriptorUuid) {
		debug('readValue(%s, %s, %s, %s)', deviceUuid, serviceUuid, characteristicUuid, descriptorUuid);

		return this._getCachedDescriptorAsync(
			deviceUuid, serviceUuid, characteristicUuid, descriptorUuid).then(descriptor => {
				return rt.promisify(descriptor.readValueAsync, descriptor)(
					BluetoothCacheMode.uncached).then(result => {
						checkCommunicationResult(deviceUuid, result);
						let data = rt.toBuffer(result.value);

						debug('  => [' + data.length + ']');
						this.emit('valueRead', deviceUuid, serviceUuid, characteristicUuid, descriptorUuid, data);
					});
			}).catch(ex => {
				debug('failed to read GATT characteristic descriptor values for device %s: %s', deviceUuid,
					ex.stack);
				this.emit('valueRead', deviceUuid, serviceUuid, characteristicUuid, descriptorUuid, ex);
			});
	};

NobleBindings.prototype.writeValue =
	function (deviceUuid, serviceUuid, characteristicUuid, descriptorUuid, data) {
		debug('writeValue(%s, %s, %s, %s, (data))',
			deviceUuid, serviceUuid, characteristicUuid, descriptorUuid);

		this._getCachedDescriptorAsync(
			deviceUuid, serviceUuid, characteristicUuid, descriptorUuid).then(descriptor => {
				let rtBuffer = rt.fromBuffer(data);
				return rt.promisify(descriptor.writeValueWithResultAsync, descriptor)(
					rtBuffer).then(result => {
						checkCommunicationResult(deviceUuid, result);
						this.emit('valueWrite', deviceUuid, serviceUuid, characteristicUuid, descriptorUuid);
					});
			}).catch(ex => {
				debug('failed to write characteristic descriptor for device %s: %s', deviceUuid, ex.stack);
				if (!withoutResponse) {
					this.emit('valueWrite', deviceUuid, serviceUuid, characteristicUuid, descriptorUuid, ex);
				}
			});
	};

NobleBindings.prototype.readHandle = function (deviceUuid, handle) {
	this.emit('readHandle', deviceUuid, handle, new Error('Not supported'));
};

NobleBindings.prototype.writeHandle = function (deviceUuid, handle, data, withoutResponse) {
	if (!withoutResponse) {
		this.emit('writeHandle', deviceUuid, handle, new Error('Not supported'));
	}
};

NobleBindings.prototype._updateRadioState = function () {
	let state;

	if (!this._radio) {
		state = 'unsupported';
	} else switch (this._radio.state) {
		case RadioState.on:
			debug('bluetooth radio is on');
			state = 'poweredOn';
			break;
		case RadioState.off:
			debug('bluetooth radio is off');
			state = 'poweredOff';
			break;
		case RadioState.disabled:
			debug('bluetooth radio is disabled');
			state = 'poweredOff';
			break;
		default:
			debug('bluetooth radio is in unknown state: ' + this._bluetoothRadio.state);
			state = 'unknown';
			break;
	}
	if (state != this._radioState) {
		this._radioState = state;
		this.emit('stateChange', state);
	}
};

NobleBindings.prototype._onAdvertisementWatcherReceived = function (sender, e) {
	let address = formatBluetoothAddress(e.bluetoothAddress);
	debug('watcher received: %s %s %s',
		getEnumName(BluetoothLEAdvertisementType, e.advertisementType),
		address,
		e.advertisement.localName);
	let deviceUuid = address.replace(/:/g, '');

	let serviceUuids = undefined;
	const isScanResponse = e.advertisementType === BluetoothLEAdvertisementType.scanResponse;
	if (isScanResponse) {
		if (!this._deviceMap[deviceUuid]) {
			debug('	Ignoring scan response for unknown device');
			return;
		}
	} else {
		if (!this._allowAdvertisementDuplicates && this._deviceMap[deviceUuid]) {
			debug('	Ignoring duplicate advertisement');
			return;
		}

		let serviceUuidMatched = !this._filterAdvertisementServiceUuids;
		serviceUuids = rt.toArray(e.advertisement.serviceUuids).map(serviceUuid => {
			if (debug.enabled) {
				debug('	service UUID: %s',
					(getEnumName(GattServiceUuids, serviceUuid) || uuidToString(serviceUuid)));
			}
			serviceUuid = uuidToString(serviceUuid);
			if (!serviceUuidMatched &&
				this._filterAdvertisementServiceUuids.indexOf(serviceUuid) >= 0) {
				serviceUuidMatched = true;
			}
			return serviceUuid;
		});
		if (!serviceUuidMatched) {
			debug('	Ignoring advertisement that did not pass service UUID filter');
			return;
		}
	}

	let connectable;
	switch (e.advertisementType) {
		case BluetoothLEAdvertisementType.connectableUndirected:
		case BluetoothLEAdvertisementType.connectableDirected:
			connectable = true;
			break;
		case BluetoothLEAdvertisementType.nonConnectableUndirected:
		case BluetoothLEAdvertisementType.scannableUndirected:
			connectable = false;
			break;
		default:
			connectable = undefined;
			break;
	}

	// Random addresses have the two most-significant bits set of the 48-bit address.
	let addressType = (e.bluetoothAddress >= (3 * Math.pow(2, 46)) ? 'random' : 'public');
	debug('	address type: %s', addressType);

	let dataSections = rt.toArray(e.advertisement.dataSections);
	let serviceDataEntry = {};
	dataSections.forEach(dataSection => {
		debug('	data section: %s',
			(getEnumName(BluetoothLEAdvertisementDataTypes, dataSection.dataType) ||
				dataSection.dataType));
		// https://www.bluetooth.com/specifications/assigned-numbers/generic-access-profile 
		switch (dataSection.dataType) {
			case BluetoothLEAdvertisementDataTypes.completeService16BitUuids:
				var id = Buffer.allocUnsafe(2);
				var buf = rt.toBuffer(dataSection.data);
				id[0] = buf[1];
				id[1] = buf[0];
				serviceDataEntry.uuid = id.toString('hex');
				break;
			case BluetoothLEAdvertisementDataTypes.completeService128BitUuids:
				serviceDataEntry.uuid = rt.toBuffer(dataSection.data).toString('hex');
				break;
			case BluetoothLEAdvertisementDataTypes.serviceData16BitUuids:
				serviceDataEntry.data = rt.toBuffer(dataSection.data).slice(2);
				break;
			default:
				break;
		}
	});

	if (typeof e.advertisement.flags === 'number') {
		debug('	advertisement flags: %s', e.advertisement.flags);
	}

	let txPowerLevel = null;
	let txPowerDataSection = dataSections.find(
		ds => ds.dataType === BluetoothLEAdvertisementDataTypes.txPowerLevel);
	if (txPowerDataSection) {
		let dataReader = DataReader.fromBuffer(txPowerDataSection.data);
		txPowerLevel = dataReader.readByte();
		if (txPowerLevel >= 128) txPowerLevel -= 256;
		dataReader.close();
	}

	let deviceRecord = this._deviceMap[deviceUuid];
	if (!deviceRecord) {
		deviceRecord = {
			name: null,
			address: e.bluetoothAddress,
			formattedAddress: address,
			addressType: addressType,
			connectable: connectable,
			serviceUuids: serviceUuids,
			txPowerLevel: null,
			device: null,
			serviceMap: {},
			characteristicMap: {},
			descriptorMap: {},
		};
		this._deviceMap[deviceUuid] = deviceRecord;
	}

	if (e.advertisement.localName) {
		deviceRecord.name = e.advertisement.localName;
	}

	var manufacturerSections = e.advertisement.manufacturerData;
	if (manufacturerSections.size > 0) {
		var manufacturerData = manufacturerSections[0];
		deviceRecord.manufacturerData = rt.toBuffer(manufacturerData.data);
		let companyIdHex = manufacturerData.companyId.toString(16);
		let toAppend = Buffer.allocUnsafe(2);
		toAppend.writeUInt16LE(manufacturerData.companyId);
		deviceRecord.manufacturerData = Buffer.concat([toAppend, deviceRecord.manufacturerData]);
		debug('	manufacturer data: %s', deviceRecord.manufacturerData.toString('hex'));
	}


	if (txPowerLevel) {
		deviceRecord.txPowerLevel = txPowerLevel;
	}

	// If only responding to scan responses, wait until the response to the active query before emitting a 'discover' event.
	if (!this._acceptOnlyScanResponse || isScanResponse) {
		let advertisement = {
			localName: deviceRecord.name,
			txPowerLevel: deviceRecord.txPowerLevel,
			manufacturerData: deviceRecord.manufacturerData, // TODO: manufacturerData
			serviceUuids: deviceRecord.serviceUuids,
			serviceData: (serviceDataEntry ? [serviceDataEntry] : []),
		};

		let rssi = e.rawSignalStrengthInDBm;

		debug('discover: %s [%s]', deviceUuid, advertisement.serviceUuids.join());
		this.emit(
			'discover',
			deviceUuid,
			address,
			deviceRecord.addressType,
			deviceRecord.connectable,
			advertisement,
			rssi);
	}
};

NobleBindings.prototype._onAdvertisementWatcherStopped = function (sender, e) {
	if (this._advertisementWatcher.status === BluetoothLEAdvertisementWatcherStatus.aborted) {
		debug('watcher aborted');
	} else if (this._advertisementWatcher.status === BluetoothLEAdvertisementWatcherStatus.stopped) {
		debug('watcher stopped');
	} else {
		debug('watcher stopped with unexpected status: %s', this._advertisementWatcher.status);
	}
	this.emit('scanStop');
};

NobleBindings.prototype._onConnectionStatusChanged = function (sender, e) {
	const deviceUuid = sender.bluetoothAddress.toString(16);
	const deviceRecord = this._deviceMap[deviceUuid];
	if (deviceRecord) {
		const connectionStatus = sender.connectionStatus;
		debug('connection status changed: ' + deviceUuid + ' ' +
			getEnumName(BluetoothConnectionStatus, connectionStatus));

		if (connectionStatus === BluetoothConnectionStatus.connected) {
			// A 'connect' event was already emitted when the device object was obtained.
			// Windows does not provide an explicit connect API; it will automatically connect
			// whenever an operation is requested on the device that requires a connection.
		}
		else if (connectionStatus === BluetoothConnectionStatus.disconnected) {
			this.disconnect(deviceUuid);
		}
	}
};

NobleBindings.prototype._getCachedServiceAsync = function (deviceUuid, serviceUuid) {
	let deviceRecord = this._deviceMap[deviceUuid];
	if (!deviceRecord) {
		throw new Error('Invalid or unknown device UUID: ' + deviceUuid);
	}

	let service = deviceRecord.serviceMap[serviceUuid];
	if (service) {
		return Promise.resolve(service);
	}

	let device = deviceRecord.device;
	if (!device) {
		throw new Error('Device is not connected. UUID: ' + deviceUuid);
	}

	return rt.promisify(device.getGattServicesAsync, device)(
		BluetoothCacheMode.cached).then(result => {
			checkCommunicationResult(deviceUuid, result);
			service = rt.trackDisposables(deviceUuid, rt.toArray(result.services))
				.find(s => uuidToString(s.uuid) === serviceUuid);
			if (!service) {
				throw new Error('Service ' + serviceUuid + ' not found for device ' + deviceUuid);
			}
			deviceRecord.serviceMap[serviceUuid] = service;
			return service;
		});
};

NobleBindings.prototype._getCachedCharacteristicAsync =
	function (deviceUuid, serviceUuid, characteristicUuid) {
		let deviceRecord = this._deviceMap[deviceUuid];
		if (!deviceRecord) {
			throw new Error('Invalid or unknown device UUID: ' + deviceUuid);
		}

		let characteristicKey = serviceUuid + '/' + characteristicUuid;
		let characteristic = deviceRecord.characteristicMap[characteristicKey];
		if (characteristic) {
			return Promise.resolve(characteristic);
		}

		return this._getCachedServiceAsync(deviceUuid, serviceUuid).then(service => {
			return rt.promisify(service.getCharacteristicsAsync, service)(
				BluetoothCacheMode.cached).then(result => {
					checkCommunicationResult(deviceUuid, result);
					characteristic = rt.toArray(result.characteristics)
						.find(c => uuidToString(c.uuid) === characteristicUuid);
					if (!characteristic) {
						throw new Error('Service ' + serviceUuid + ' characteristic ' +
							characteristicUuid + ' not found for device ' + deviceUuid);
					}
					deviceRecord.characteristicMap[characteristicKey] = characteristic;
					return characteristic;
				});
		});
	};

NobleBindings.prototype._getCachedDescriptorAsync =
	function (deviceUuid, serviceUuid, characteristicUuid, descriptorUuid) {
		let deviceRecord = this._deviceMap[deviceUuid];
		if (!deviceRecord) {
			throw new Error('Invalid or unknown device UUID: ' + deviceUuid);
		}

		let descriptorKey = serviceUuid + '/' + characteristicUuid + '/' + descriptorUuid;
		let descriptor = deviceRecord.descriptorMap[descriptorKey];
		if (descriptor) {
			return Promise.resolve(descriptor);
		}

		return this._getCachedCharacteristicAsync(
			deviceUuid, serviceUuid, characteristicUuid).then(characteristic => {
				return rt.promisify(characteristic.getDescriptorsAsync, characteristic)(
					BluetoothCacheMode.cached).then(result => {
						checkCommunicationResult(deviceUuid, result);
						descriptor = rt.toArray(result.descriptors)
							.find(d => uuidToString(d.uuid) === descriptorUuid);
						if (!descriptor) {
							throw new Error('Service ' + serviceUuid + ' characteristic ' +
								characteristicUuid + ' descriptor ' + descriptorUuid +
								' not found for device ' + deviceUuid);
						}
						deviceRecord.descriptorMap[descriptorKey] = descriptor;
						return descriptor;
					});
			});
	};

function formatBluetoothAddress(address) {
	if (!address) {
		return 'null';
	}

	let formattedAddress = address.toString(16);
	while (formattedAddress.length < 12) {
		formattedAddress = '0' + formattedAddress;
	}
	formattedAddress =
		formattedAddress.substr(0, 2) + ':' +
		formattedAddress.substr(2, 2) + ':' +
		formattedAddress.substr(4, 2) + ':' +
		formattedAddress.substr(6, 2) + ':' +
		formattedAddress.substr(8, 2) + ':' +
		formattedAddress.substr(10, 2);
	return formattedAddress;
}

function characteristicPropertiesToStrings(props) {
	let strings = [];

	if (props & GattCharacteristicProperties.broadcast) {
		strings.push('broadcast');
	}

	if (props & GattCharacteristicProperties.read) {
		strings.push('read');
	}

	if (props & GattCharacteristicProperties.writeWithoutResponse) {
		strings.push('writeWithoutResponse');
	}

	if (props & GattCharacteristicProperties.write) {
		strings.push('write');
	}

	if (props & GattCharacteristicProperties.notify) {
		strings.push('notify');
	}

	if (props & GattCharacteristicProperties.indicate) {
		strings.push('indicate');
	}

	if (props & GattCharacteristicProperties.broadcast) {
		strings.push('authenticatedSignedWrites');
	}

	if (props & GattCharacteristicProperties.extendedProperties) {
		strings.push('extendedProperties');
	}

	return strings;
}

function getEnumName(enumType, value) {
	return Object.keys(enumType).find(enumName =>
		value === enumType[enumName]);
}

function stringToUuid(uuid) {
	if (typeof (uuid) === 'number') {
		return BluetoothUuidHelper.fromShortId(uuid).replace(/[{}]/g, '');
	} else if (uuid && uuid.length === 4) {
		return BluetoothUuidHelper.fromShortId(parseInt(uuid, 16)).replace(/[{}]/g, '');
	} else {
		return uuid;
	}
}

function uuidToString(uuid) {
	if (!uuid) {
		return uuid;
	}
	uuid = uuid.toString().replace(/[{}]/g, '');
	let shortId = BluetoothUuidHelper.tryGetShortId(uuid);
	if (shortId) {
		return uint32ToHexString(shortId);
	} else {
		return uuid.replace(/-/g, '').toLowerCase();
	}
}

function uint32ToHexString(n) {
	return (n + 0x10000).toString(16).substr(-4);
}

function filterUuids(filter) {
	return (uuid) => {
		return !filter || filter.indexOf(uuid) != -1;
	};
}

function checkCommunicationResult(deviceUuid, result) {
	if (result.status === GattCommunicationStatus.unreachable) {
		throw new Error('Device unreachable: ' + deviceUuid);
	} else if (result.status === GattCommunicationStatus.protocolError) {
		throw new Error('Protocol error communicating with device: ' + deviceUuid);
	}
}

module.exports = new NobleBindings();
