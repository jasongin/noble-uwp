'use strict';

// NobleUWPAddition is to expand noble interface with additional features, known to be supported on UWP.

const debug = require('debug')('noble-uwp');
const rt = require('./rt-utils');

// Note the load order here is important for cross-namespace dependencies.
rt.using('Windows.Devices.Bluetooth');

const BluetoothSignalStrengthFilter = Windows.Devices.Bluetooth.BluetoothSignalStrengthFilter;

let NobleUWPAddition = function () {
	this.bindings = null;
	this.init = function (bindings) {
		this.bindings = bindings;
	}
	this.acceptOnlyScanResponse = function (value) {
		if (!this.bindings) {
			debug('bindings is not set, initialize this component.');
			return;
		}
		this.bindings._acceptOnlyScanResponse = value;
	}
	this.setSignalFilter = function (inRangeThreshold, outOfRangeThreshold, outOfRangeTimeout, samplingInterval) {
		try {
			if (!this.bindings) {
				debug('bindings is not set, initialize this component.');
				return;
			}
			if (!this.bindings._advertisementWatcher) {
				debug('AdvertisementWatcher is not set.');
				return;
			}
			let signalFilter = new BluetoothSignalStrengthFilter();
			signalFilter.inRangeThresholdInDBm = inRangeThreshold;
			signalFilter.outOfRangeThresholdInDBm = outOfRangeThreshold;
			signalFilter.outOfRangeTimeout = outOfRangeTimeout;
			signalFilter.samplingInterval = samplingInterval;
			this.bindings._advertisementWatcher.signalStrengthFilter = signalFilter;
		} catch (error) {
			debug('setSignalConfig error: ' + error.stack);
		}
	}
}

module.exports = new NobleUWPAddition();