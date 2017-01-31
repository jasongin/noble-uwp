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

const BluetoothLEAdvertisementWatcher = Windows.Devices.Bluetooth.Advertisement.BluetoothLEAdvertisementWatcher;
const BluetoothLEScanningMode = Windows.Devices.Bluetooth.Advertisement.BluetoothLEScanningMode;
const BluetoothLEAdvertisementType = Windows.Devices.Bluetooth.Advertisement.BluetoothLEAdvertisementType;
const BluetoothLEAdvertisementDataTypes = Windows.Devices.Bluetooth.Advertisement.BluetoothLEAdvertisementDataTypes;
const BluetoothLEAdvertisementWatcherStatus = Windows.Devices.Bluetooth.Advertisement.BluetoothLEAdvertisementWatcherStatus;

const GattDeviceService = Windows.Devices.Bluetooth.GenericAttributeProfile.GattDeviceService;
const GattServiceUuids = Windows.Devices.Bluetooth.GenericAttributeProfile.GattServiceUuids;
const GattCommunicationStatus = Windows.Devices.Bluetooth.GenericAttributeProfile.GattCommunicationStatus;
const GattClientCharacteristicConfigurationDescriptorValue = Windows.Devices.Bluetooth.GenericAttributeProfile.GattClientCharacteristicConfigurationDescriptorValue;

const Radio = Windows.Devices.Radios.Radio;
const RadioKind = Windows.Devices.Radios.RadioKind;
const RadioState = Windows.Devices.Radios.RadioState;

const DataReader = Windows.Storage.Streams.DataReader;

function debugErrors(fn) {
	return function () {
		try {
			return fn.apply(null, arguments);
		} catch (ex) {
			debug(ex.stack);
		}
	};
}

var NobleBindings = function() {
	this._radio = null;
	this._radioState = 'unknown';
	this._deviceMap = {};
	this._listenerCount = 0;
	this._listenerTimeoutId = 0;
	this._listenerMap = {};
};

util.inherits(NobleBindings, events.EventEmitter);

NobleBindings.prototype.init = function() {
	this._advertisementWatcher = new BluetoothLEAdvertisementWatcher();
	this._advertisementWatcher.scanningMode = BluetoothLEScanningMode.active;
	this._advertisementWatcher.on('received', debugErrors(this._onAdvertisementWatcherReceived.bind(this)));
	this._advertisementWatcher.on('stopped', debugErrors(this._onAdvertisementWatcherStopped.bind(this)));
	this._advertisementTimeoutId = null;

	debug('initialized');

	rt.promisify(Radio.getRadiosAsync)().then(radiosList => {
		radiosList = rt.toArray(radiosList);
		this._radio = radiosList.find(radio => radio.kind === RadioKind.bluetooth);
		if (this._radio) {
			debug('found bluetooth radio: ' + this._radio.name);
		} else {
			debug('no bluetooth radio found');
		}
		this._updateRadioState();
	}).catch(ex => {
		debug('failed to get radios: ' + ex.stack);
		this._updateRadioState();
	});
};

NobleBindings.prototype.startScanning = function(serviceUuids, allowDuplicates) {
	if (this._advertisementTimeoutId === null) {
		allowDuplicates = !!allowDuplicates;
		debug('startScanning(' + (serviceUuids ? serviceUuids.join() : '') + ', ' + allowDuplicates + ')');
		this._advertisementWatcher.start();
		this._advertisementTimeoutId = setTimeout(() => {}, 10000000);
	}
};

NobleBindings.prototype.stopScanning = function() {
	debug('stopScanning()');
	this._advertisementWatcher.stop();
	clearTimeout(this._advertisementTimeoutId);
	this._advertisementTimeoutId = null;
};

NobleBindings.prototype.connect = function(deviceUuid) {
	debug('connect(' + deviceUuid + ')');

	var deviceRecord = this._deviceMap[deviceUuid];
	if (!deviceRecord) {
		throw new Error('Invalid or unknown device UUID: ' + deviceUuid);
	}

	if (!deviceRecord.connectable) {
		throw new Error("Device is not connectable: " + deviceRecord.formattedAddress);
	}

	rt.promisify(BluetoothLEDevice.fromBluetoothAddressAsync)(deviceRecord.address).then(device => {
		debug('got bluetooth device: ' + device.name + ' (' + device.deviceInformation.kind + ')');
		deviceRecord.device = device;

		this.emit('connect', deviceUuid, null);
	}).catch(ex => {
		debug('failed to get device ' + deviceRecord.formattedAddress + ': ' + ex.stack);
		this.emit('connect', deviceUuid, ex);
	});
};

NobleBindings.prototype.disconnect = function(deviceUuid) {
	debug('disconnect(' + deviceUuid + ')');

	let deviceRecord = this._deviceMap[deviceUuid];
	if (!deviceRecord) {
		throw new Error('Invalid or unknown device UUID: ' + deviceUuid);
	}

	deviceRecord.device = null;

	this.emit('disconnect', deviceUuid);
};

NobleBindings.prototype.updateRssi = function(deviceUuid) {
	debug('updateRssi(' + deviceUuid + ')');

	// TODO: Retrieve updated RSSI
	let rssi = 0;

	this.emit('rssiUpdate', deviceUuid, rssi);
};

NobleBindings.prototype.discoverServices = function(deviceUuid, filterServiceUuids) {
	if (filterServiceUuids && filterServiceUuids.length === 0) {
		filterServiceUuids = null;
	}
	
	debug('discoverServices(' + deviceUuid + ', ' +
		(filterServiceUuids ? filterServiceUuids.join() : '(all)') + ')');

	let deviceRecord = this._deviceMap[deviceUuid];
	if (!deviceRecord) {
		throw new Error('Invalid or unknown device UUID: ' + deviceUuid);
	}

	let device = deviceRecord.device;
	if (!device) {
		throw new Error('Device is not connected. UUID: ' + deviceUuid);
	}

	// TODO: Optimize by using cached mode when the services were already discovered.
	rt.promisify(device.getGattServicesAsync, device)(
			BluetoothCacheMode.uncached).then(result => {
		checkCommunicationResult(deviceUuid, result);

		let services = rt.toArray(result.services);
		let serviceUuids = services.map(s => formatUuid(s.uuid))
			.filter(filterUuids(filterServiceUuids));

		debug(deviceUuid + ' services: ' + serviceUuids);
		this.emit('servicesDiscover', deviceUuid, serviceUuids);
	}).catch(ex => {
		debug('failed to get GATT services for device ' + deviceUuid + ': ' + ex.stack);
		this.emit('servicesDiscover', deviceUuid, ex);
	});
};

NobleBindings.prototype.discoverIncludedServices = function(deviceUuid, serviceUuid, filterServiceUuids) {
	if (filterServiceUuids && filterServiceUuids.length === 0) {
		filterServiceUuids = null;
	}
	
	debug('discoverIncludedServices(' + deviceUuid + ', ' + serviceUuid + ', ' +
		(filterServiceUuids ? filterServiceUuids.join() : '(all)') + ')');

	this._getCachedServiceAsync(deviceUuid, serviceUuid).then(service => {
		// TODO: Optimize by using cached mode when included services were already discovered.
		rt.promisify(service.getIncludedServicesAsync, service)(
				BluetoothCacheMode.uncached).then(result => {
			checkCommunicationResult(deviceUuid, result);

			let includedServices = rt.toArray(result.services);
			let includedServiceUuids = includedServices.map(s => formatUuid(s.uuid))
				.filter(filterUuids(filterServiceUuids));

			debug(deviceUuid + ' ' + serviceUuid + ' included services: ' + includedServiceUuids);
			this.emit('includedServicesDiscover', deviceUuid, serviceUuid, includedServiceUuids);
		});
	}).catch(ex => {
		debug('failed to get GATT included services for device ' +
			deviceUuid + ': ' + ex.stack);
		this.emit('includedServicesDiscover', deviceUuid, serviceUuid, ex);
	});
};

NobleBindings.prototype.discoverCharacteristics = function(deviceUuid, serviceUuid, filterCharacteristicUuids) {
	if (filterCharacteristicUuids && filterCharacteristicUuids.length === 0) {
		filterCharacteristicUuids = null;
	}

	debug('discoverCharacteristics(' + deviceUuid + ', ' + serviceUuid + ', ' +
		(filterCharacteristicUuids ? filterCharacteristicUuids.join() : '(all)') + ')');

	this._getCachedServiceAsync(deviceUuid, serviceUuid).then(service => {
		// TODO: Optimize by using cached mode when characteristics were already discovered.
		return rt.promisify(service.getCharacteristicsAsync, service)(
				BluetoothCacheMode.uncached).then(result => {
			checkCommunicationResult(deviceUuid, result);

			let characteristics = rt.toArray(result.characteristics)
				.filter(filterUuids(filterCharacteristicUuids))
				.map(c => {
					let d = {
						uuid: formatUuid(c.uuid),
						properties: [],
					};
					// TODO: Map c.characteristicProperties bits to string properties.
					return d;
				});

			debug(deviceUuid + ' ' + serviceUuid + ' characteristics: ' +
				characteristics.map(c => c.uuid));
			this.emit('characteristicsDiscover', deviceUuid, serviceUuid, characteristics);
		});
	}).catch(ex => {
		debug('failed to get GATT characteristics for device ' +
			deviceUuid + ': ' + ex.stack);
		this.emit('characteristicsDiscover', deviceUuid, serviceUuid, ex);
	});
};

NobleBindings.prototype.read = function(deviceUuid, serviceUuid, characteristicUuid) {
	debug('read(' + deviceUuid + ', ' + serviceUuid + ', ' + characteristicUuid + ')');

	this._getCachedCharacteristicAsync(
			deviceUuid, serviceUuid, characteristicUuid).then(characteristic => {
		return rt.promisify(characteristic.readValueAsync, characteristic)().then(result => {
			checkCommunicationResult(deviceUuid, result);
			let data = rt.toBuffer(result.value);

			debug('  => [' + data.length + ']');
			this.emit('read', deviceUuid, serviceUuid, characteristicUuid, data, false);
		});
	}).catch (ex => {
		debug('failed to read characteristic for device ' + deviceUuid + ': ' + ex.stack);
		this.emit('read', deviceUuid, serviceUuid, characteristicUuid, ex, false);
	});
};

NobleBindings.prototype.write =
		function(deviceUuid, serviceUuid, characteristicUuid, data, withoutResponse) {
	debug('write(' + deviceUuid + ', ' + serviceUuid + ', ' + characteristicUuid + ', (data), ' +
		withoutResponse + ')');

	this._getCachedCharacteristicAsync(
			deviceUuid, serviceUuid, characteristicUuid).then(characteristic => {
		var rtBuffer = rt.fromBuffer(data);
		return rt.promisify(characteristic.writeValueWithResultAsync, characteristic)(
				rtBuffer).then(result => {
			checkCommunicationResult(deviceUuid, result);
			this.emit('write', deviceUuid, serviceUuid, characteristicUuid);
		});
	}).catch(ex => {
		debug('failed to write characteristic for device ' + deviceUuid + ': ' + ex.stack);
		if (!withoutResponse) {
			this.emit('write', deviceUuid, serviceUuid, characteristicUuid, ex);
		}
	});
};

NobleBindings.prototype.broadcast =
		function(deviceUuid, serviceUuid, characteristicUuid, broadcast) {
	debug('broadcast(' + deviceUuid + ', ' + serviceUuid + ', ' + characteristicUuid + ', ' +
		broadcast + ')');

	this.emit('broadcast', deviceUuid, serviceUuid, characteristicUuid,
		new Error('Not implemented'));
};

NobleBindings.prototype.notify = function(deviceUuid, serviceUuid, characteristicUuid, notify) {
	debug('notify(' + deviceUuid + ', ' + serviceUuid + ', ' + characteristicUuid + ', ' +
		notify + ')');

	this._getCachedCharacteristicAsync(
			deviceUuid, serviceUuid, characteristicUuid).then(characteristic => {
		let listenerKey = deviceUuid + '/' + serviceUuid + '/' + characteristicUuid;
		let listener = this._listenerMap[listenerKey];

		if (notify) {
			if (listener) {
				// Already listening.
				this.emit('notify', deviceUuid, serviceUuid, characteristicUuid, notify);
				return;
			}
			
			return rt.promisify(
					characteristic.writeClientCharacteristicConfigurationDescriptorWithResultAsync,
					characteristic)(GattClientCharacteristicConfigurationDescriptorValue.notify)
					.then(result => {
				checkCommunicationResult(deviceUuid, result);

				let bindings = this;
				listener = (source, e) => {
					debug('notification: ' + deviceUuid + ' ' + serviceUuid + ' ' + characteristicUuid);
					let data = rt.toBuffer(e.characteristicValue);
					bindings.emit('read', deviceUuid, serviceUuid, characteristicUuid, data, true);
				}

				characteristic.addListener('valueChanged', listener);
				this._listenerMap[listenerKey] = listener;

				if (++this._listenerCount == 1) {
					// Set an interval to keep the engine alive while there's an event listener.
					// The actual duration doesn't really matter: it should be large but not too large.
					this._listenerTimeoutId = setInterval(() => {}, 24 * 60 * 60 * 1000);
				}

				this.emit('notify', deviceUuid, serviceUuid, characteristicUuid, notify);
			});
		} else {
			if (!listener) {
				// Already not listening.
				this.emit('notify', deviceUuid, serviceUuid, characteristicUuid, notify);
				return;
			}

			if (--this._listenerCount == 0) {
				// Stop keeping the engine alive because there are no more event listeners.
				clearInterval(this._listenerTimeoutId);
			}

			characteristic.removeListener('valueChanged', listener);
			delete this._listenerMap[listenerKey];

			return rt.promisify(
					characteristic.writeClientCharacteristicConfigurationDescriptorWithResultAsync,
					characteristic)(GattClientCharacteristicConfigurationDescriptorValue.none)
					.then(result => {
				checkCommunicationResult(deviceUuid, result);

				this.emit('notify', deviceUuid, serviceUuid, characteristicUuid, notify);
			});
		}
	}).catch(ex => {
		debug('failed to enable characteristic notify for device ' + deviceUuid + ': ' + ex.stack);
		this.emit('notify', deviceUuid, serviceUuid, characteristicUuid, ex);
	});
};

NobleBindings.prototype.discoverDescriptors =
		function(deviceUuid, serviceUuid, characteristicUuid) {
	debug('discoverDescriptors(' + deviceUuid + ', ' + serviceUuid + ', ' +
		characteristicUuid + ')');

	this.emit('descriptorsDiscover', deviceUuid, serviceUuid, characteristicUuid,
		new Error('Not implemented'));
};

NobleBindings.prototype.readValue =
		function(deviceUuid, serviceUuid, characteristicUuid, descriptorUuid) {
	debug('readValue(' + deviceUuid + ', ' + serviceUuid + ', ' + characteristicUuid + ', ' +
		descriptorUuid + ')');

	this.emit('readValue', deviceUuid, serviceUuid, characteristicUuid, descriptorUuid,
		new Error('Not implemented'));
};

NobleBindings.prototype.writeValue =
		function(deviceUuid, serviceUuid, characteristicUuid, descriptorUuid, data) {
	debug('writeValue(' + deviceUuid + ', ' + serviceUuid + ', ' + characteristicUuid + ', ' +
		descriptorUuid + ', (data))');

	this.emit('writeValue', deviceUuid, serviceUuid, characteristicUuid, descriptorUuid,
		new Error('Not implemented'));
};

NobleBindings.prototype.readHandle = function(deviceUuid, handle) {
	debug('readHandle(' + deviceUuid + ', ' + handle + ')');

	this.emit('readHandle', deviceUuid, handle, new Error('Not implemented'));
};

NobleBindings.prototype.writeHandle = function(deviceUuid, handle, data, withoutResponse) {
	debug('writeHandle(' + deviceUuid + ', ' + handle + ', (data), ' + withoutResponse + ')');

	if (!withoutResponse) {
		this.emit('writeHandle', deviceUuid, handle, new Error('Not implemented'));
	}
};

NobleBindings.prototype._updateRadioState = function() {
	var state;

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
}

NobleBindings.prototype._onAdvertisementWatcherReceived = function(sender, e) {
	var address = formatBluetoothAddress(e.bluetoothAddress);
	debug('watcher received: ' + address + ' ' + e.advertisement.localName);

	debug('    advertisement type: ' +
		getEnumName(BluetoothLEAdvertisementType, e.advertisementType));

	var dataSections = rt.toArray(e.advertisement.dataSections);
	dataSections.forEach(dataSection => {
		debug('    data section: ' +
			(getEnumName(BluetoothLEAdvertisementDataTypes, dataSection.dataType) ||
			dataSection.dataType));
	});

	debug('    flags: ' + e.advertisement.flags);

	var deviceUuid = address.replace(/:/g, '');
	var rssi = e.rawSignalStrengthInDBm;

	var connectable;
	switch (e.advertisementType) {
		case BluetoothLEAdvertisementType.connectableUndirected:
		case BluetoothLEAdvertisementType.connectableDirected:
			connectable = true;
			break;
		case BluetoothLEAdvertisementType.scanResponse:
			connectable = null;
			break;
		default:
			connectable = false;
			break;
	}

	var txPowerLevel = null;
	var dataSections = rt.toArray(e.advertisement.dataSections);
	var txPowerDataSection = dataSections.find(
		ds => ds.dataType === BluetoothLEAdvertisementDataTypes.txPowerLevel);
	if (txPowerDataSection) {
		var dataReader = DataReader.fromBuffer(txPowerDataSection.data);
		txPowerLevel = dataReader.readByte();
		if (txPowerLevel >= 128) txPowerLevel -= 256;
		dataReader.close();
	}

	var serviceUuids = rt.toArray(e.advertisement.serviceUuids);
	serviceUuids.forEach(serviceUuid => {
		debug('    service UUID: ' + (getEnumName(GattServiceUuids, serviceUuid) || serviceUuid));
	});

	// TODO: Check device.bluetoothAddressType property.
	var addressType = 'unknown';

	var deviceRecord = this._deviceMap[deviceUuid];
	if (!deviceRecord) {
		deviceRecord = {
			name: null,
			address: e.bluetoothAddress,
			formattedAddress: address,
			addressType: addressType,
			connectable: connectable,
			serviceUuids: [],
			txPowerLevel: null,
			device: null,
			serviceMap: {},
			characteristicMap: {},
		};
		this._deviceMap[deviceUuid] = deviceRecord;
	}

	if (e.advertisement.localName) {
		deviceRecord.name = e.advertisement.localName;
	}
	if (serviceUuids) {
		serviceUuids.forEach(serviceUuid => {
			if (deviceRecord.serviceUuids.indexOf(serviceUuid) < 0) {
				deviceRecord.serviceUuids.push(serviceUuid);
			}
		});
	}
	if (txPowerLevel) {
		deviceRecord.txPowerLevel = txPowerLevel;
	}

	var advertisement = {
		localName: deviceRecord.name,
		txPowerLevel: deviceRecord.txPowerLevel,
		manufacturerData: null, // TODO: manufacturerData
		serviceUuids: deviceRecord.serviceUuids,
		serviceData: [], // TODO: serviceData
	};

	// Wait until a name is received before "discovering" this device. The (second)
	// advertisement packet, in response to the active query, should contain a name.
	if (deviceRecord.name) {
		this.emit(
			'discover',
			 deviceUuid,
			 address,
			 deviceRecord.addressType,
			 deviceRecord.connectable,
			 advertisement, rssi);
	}
}

NobleBindings.prototype._onAdvertisementWatcherStopped = function(sender, e) {
	if (this._advertisementWatcher.status === BluetoothLEAdvertisementWatcherStatus.aborted) {
		debug('watcher aborted');
	} else if (this._advertisementWatcher.status === BluetoothLEAdvertisementWatcherStatus.stopped) {
		debug('watcher stopped');
	} else {
		debug('watcher stopped with unexpected status: ' + this._advertisementWatcher.status);
	}
}

NobleBindings.prototype._getCachedServiceAsync = function(deviceUuid, serviceUuid) {
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
		service = rt.toArray(result.services)
			.find(s => formatUuid(s.uuid) === serviceUuid);
		if (!service) {
			throw new Error('Service ' + serviceUuid + ' not found for device ' + deviceUuid);
		}
		deviceRecord.serviceMap[serviceUuid] = service;
		return service;
	});
}

NobleBindings.prototype._getCachedCharacteristicAsync =
		function(deviceUuid, serviceUuid, characteristicUuid) {
	let deviceRecord = this._deviceMap[deviceUuid];
	if (!deviceRecord) {
		throw new Error('Invalid or unknown device UUID: ' + deviceUuid);
	}

	let characteristic = deviceRecord.characteristicMap[characteristicUuid];
	if (characteristic) {
		return Promise.resolve(characteristic);
	}

	return this._getCachedServiceAsync(deviceUuid, serviceUuid).then(service => {
		return rt.promisify(service.getCharacteristicsAsync, service)(
				BluetoothCacheMode.cached).then(result => {
			checkCommunicationResult(deviceUuid, result);
			characteristic = rt.toArray(result.characteristics)
				.find(c => formatUuid(c.uuid) === characteristicUuid);
			if (!characteristic) {
				throw new Error('Service ' + serviceUuid + ' characteristic ' +
					characteristicUuid + ' not found for device ' + deviceUuid);
			}
			deviceRecord.characteristicMap[characteristicUuid] = characteristic;
			return characteristic;
		});
	});
}

function formatBluetoothAddress(address) {
	if (!address) {
		return 'null';
	}

	var formattedAddress = address.toString(16);
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

function getEnumName(enumType, value) {
	return Object.keys(enumType).find(enumName =>
		value === enumType[enumName]);
}

function formatUuid(uuid) {
	if (!uuid) {
		return uuid;
	} else if (/{0000[0-9A-F]{4}-0000-1000-8000-00805F9B34FB}/i.test(uuid)) {
		return uuid.substr(5, 4).toLowerCase();
	} else {
		return uuid.replace(/[-{}]/g, '').toLowerCase();
	}
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
