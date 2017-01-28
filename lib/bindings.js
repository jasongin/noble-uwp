const events = require('events');
const util = require('util');

const debug = require('debug')('noble-uwp');

const rt = require('./rt-utils');

const Windows = {
	Devices: {},
	Storage: {},
};
Windows.Foundation = require('../uwp/windows.foundation');
Windows.Devices.Bluetooth = require('../uwp/windows.devices.bluetooth');
Windows.Devices.Bluetooth.Advertisement = require('../uwp/windows.devices.bluetooth.advertisement');
Windows.Devices.Bluetooth.GenericAttributeProfile = require('../uwp/windows.devices.bluetooth.genericattributeprofile');
Windows.Devices.Enumeration = require('../uwp/windows.devices.enumeration');
Windows.Devices.Radios = require('../uwp/windows.devices.radios');
Windows.Storage.Streams = require('../uwp/windows.storage.streams');

const BluetoothLEDevice = Windows.Devices.Bluetooth.BluetoothLEDevice;

const BluetoothLEAdvertisementWatcher = Windows.Devices.Bluetooth.Advertisement.BluetoothLEAdvertisementWatcher;
const BluetoothLEScanningMode = Windows.Devices.Bluetooth.Advertisement.BluetoothLEScanningMode;
const BluetoothLEAdvertisementType = Windows.Devices.Bluetooth.Advertisement.BluetoothLEAdvertisementType;
const BluetoothLEAdvertisementDataTypes = Windows.Devices.Bluetooth.Advertisement.BluetoothLEAdvertisementDataTypes;
const BluetoothLEAdvertisementWatcherStatus = Windows.Devices.Bluetooth.Advertisement.BluetoothLEAdvertisementWatcherStatus;

const GattDeviceService = Windows.Devices.Bluetooth.GenericAttributeProfile.GattDeviceService;
const GattServiceUuids = Windows.Devices.Bluetooth.GenericAttributeProfile.GattServiceUuids;

const Radio = Windows.Devices.Radios.Radio;
const RadioKind = Windows.Devices.Radios.RadioKind;
const RadioState = Windows.Devices.Radios.RadioState;

function debugErrors(fn) {
	return function () {
		try {
			return fn.apply(null, arguments);
		} catch (e) {
			debug(e.stack);
		}
	};
}

var NobleBindings = function() {
	this._radio = null;
	this._radioState = 'unknown';
	this._deviceMap = {};
};

util.inherits(NobleBindings, events.EventEmitter);

NobleBindings.prototype.init = function() {
	this._advertisementWatcher = new BluetoothLEAdvertisementWatcher();
	this._advertisementWatcher.scanningMode = BluetoothLEScanningMode.active;
	this._advertisementWatcher.on('received', debugErrors(this._onAdvertisementWatcherReceived.bind(this)));
	this._advertisementWatcher.on('stopped', debugErrors(this._onAdvertisementWatcherStopped.bind(this)));

	debug('initialized');

	rt.promisify(Radio.getRadiosAsync)().then(debugErrors(radiosList => {
		radiosList = rt.toArray(radiosList);
		this._radio = radiosList.find(radio => radio.kind === RadioKind.bluetooth);
		if (this._radio) {
			debug('found bluetooth radio: ' + this._radio.name);
		} else {
			debug('no bluetooth radio found');
		}
		this._updateRadioState();
	}), e => {
		debug('failed to get radios: ' + e.message);
	});
};

NobleBindings.prototype.startScanning = function(serviceUuids, allowDuplicates) {
	allowDuplicates = !!allowDuplicates;
	debug('startScanning(' + (serviceUuids ? serviceUuids.join() : '') + ', ' + allowDuplicates + ')');
	this._advertisementWatcher.start();
	this._advertisementTimeoutId = setTimeout(() => {}, 10000000);
};

NobleBindings.prototype.stopScanning = function() {
	debug('stopScanning()');
	this._advertisementWatcher.stop();
	clearTimeout(this._advertisementTimeoutId);
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

	BluetoothLEDevice.fromBluetoothAddressAsync(deviceRecord.address).then(debugErrors(device => {
		debug('got bluetooth device: ' + device.name + ' (' + device.deviceInformation.kind + ')');
		deviceRecord.device = device;

		var deviceProperties = rt.toMap(device.deviceInformation.properties);
		deviceProperties.keys().forEach(propertyKey => {
			var v = deviceProperties[propertyKey];

			if (typeof v === 'object') {
				v.__proto__ = Windows.Foundation.IPropertyValue.prototype;
			}

			debug('    ' + propertyKey + ' = ' + v);
		});

		rt.promisify(device.getGattServicesAsync, device)().then(debugErrors(gattServices => {
			var services = rt.toArray(gattServices.services);
			services.forEach(s => {
				debug('    service: ' + s);
			});
		}), error => {
			debug('failed to get GATT services for device ' +
				deviceRecord.formattedAddress + ': ' + error.message);
			this.emit('connect', deviceUuid, error);
		});
	}), error => {
		debug('failed to get device ' + deviceRecord.formattedAddress + ': ' + error.message);
		this.emit('connect', deviceUuid, error);
	});
};

NobleBindings.prototype.disconnect = function(deviceUuid) {
	debug('disconnect(' + deviceUuid + ')');

	// TODO: device.deviceInformation.pairing.unpairAsync
};

NobleBindings.prototype.updateRssi = function(deviceUuid) {
	debug('updateRssi(' + deviceUuid + ')');
};

NobleBindings.prototype.discoverServices = function(deviceUuid, uuids) {
	debug('discoverServices(' + deviceUuid + ', ' + (uuids ? uuids.join() : '(all)') + ')');

	var deviceRecord = this._deviceMap[deviceUuid];
	if (!deviceRecord) {
		throw new Error('Invalid or unknown device UUID: ' + deviceUuid);
	}

	var device = deviceRecord.device;
	if (!device) {
		throw new Error('Device is not connected. UUID: ' + deviceUuid);
	}

	// TODO: Discover services
};

NobleBindings.prototype.discoverIncludedServices = function(deviceUuid, serviceUuid, serviceUuids) {
	debug('discoverIncludedServices(' + deviceUuid + ', ' + serviceUuid + ', ' + (serviceUuids ? serviceUuids.join() : '(all)') + ')');
};

NobleBindings.prototype.discoverCharacteristics = function(deviceUuid, serviceUuid, characteristicUuids) {
	debug('discoverCharacteristics(' + deviceUuid + ', ' + serviceUuid + ', ' + (characteristicUuids ? characteristicUuids.join() : '(all)') + ')');
};

NobleBindings.prototype.read = function(deviceUuid, serviceUuid, characteristicUuid) {
	debug('read(' + deviceUuid + ', ' + serviceUuid + ', ' + characteristicUuid + ')');
};

NobleBindings.prototype.write = function(deviceUuid, serviceUuid, characteristicUuid, data, withoutResponse) {
	debug('write(' + deviceUuid + ', ' + serviceUuid + ', ' + characteristicUuid + ', (data), ' + withoutResponse + ')');
};

NobleBindings.prototype.broadcast = function(deviceUuid, serviceUuid, characteristicUuid, broadcast) {
	debug('broadcast(' + deviceUuid + ', ' + serviceUuid + ', ' + characteristicUuid + ', ' + broadcast + ')');
};

NobleBindings.prototype.notify = function(deviceUuid, serviceUuid, characteristicUuid, notify) {
	debug('notify(' + deviceUuid + ', ' + serviceUuid + ', ' + characteristicUuid + ', ' + notify + ')');
};

NobleBindings.prototype.discoverDescriptors = function(deviceUuid, serviceUuid, characteristicUuid) {
	debug('discoverDescriptors(' + deviceUuid + ', ' + serviceUuid + ', ' + characteristicUuid + ')');
};

NobleBindings.prototype.readValue = function(deviceUuid, serviceUuid, characteristicUuid, descriptorUuid) {
	debug('readValue(' + deviceUuid + ', ' + serviceUuid + ', ' + characteristicUuid + ', ' + descriptorUuid + ')');
};

NobleBindings.prototype.writeValue = function(deviceUuid, serviceUuid, characteristicUuid, descriptorUuid, data) {
	debug('writeValue(' + deviceUuid + ', ' + serviceUuid + ', ' + characteristicUuid + ', ' + descriptorUuid + ', (data))');
};

NobleBindings.prototype.readHandle = function(deviceUuid, handle) {
	debug('readHandle(' + deviceUuid + ', ' + handle + ')');
};

NobleBindings.prototype.writeHandle = function(deviceUuid, handle, data, withoutResponse) {
	debug('readHandle(' + deviceUuid + ', ' + handle + ', (data), ' + withoutResponse + ')');
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

	debug('    advertisement type: ' + getEnumName(BluetoothLEAdvertisementType, e.advertisementType));

	var dataSections = rt.toArray(e.advertisement.dataSections);
	dataSections.forEach(dataSection => {
		debug('    data section: ' + (getEnumName(BluetoothLEAdvertisementDataTypes, dataSection.dataType) || dataSection.dataType));
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

	var addressType = 'unknown';

	/*
	BluetoothLEDevice.fromBluetoothAddressAsync(e.bluetoothAddress).then(debugErrors(device => {
		debug('got bluetooth device: ' + device.name);

		switch (device.bluetoothAddressType) {
			case BluetoothAddressType.public: addressType = 'public'; break;
			case BluetoothAddressType.random: addressType = 'random'; break;
			default: addressType = 'unknown'; break;
		}

		GattDeviceService.fromIdAsync(device.deviceId).then(deviceService => {
			debug('got device service');
		}, error => {
			debug('failed to get device service: ' + error.message);
		});

		this.emit('discover', deviceUuid, address, addressType, connectable, advertisement, rssi);
	}), error => {
		debug('failed to get device ' + address + ': ' + error.message);
	});
	*/

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

	// Wait until a name is received before "discovering" this device. The (second) advertisement packet,
	// in response to the active query, should contain a name.
	if (deviceRecord.name) {
		this.emit('discover', deviceUuid, address, deviceRecord.addressType, deviceRecord.connectable, advertisement, rssi);
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

function formatBluetoothAddress(address) {
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

module.exports = new NobleBindings();
