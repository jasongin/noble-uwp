'use strict';

const os = require('os');

// noble-uwp acts as a shim to noble. If Windows >= 10.0.15014, it will bind UWP to noble interface
// Otherwise, it will either fail (on Windows), or revert back to noble (noble does not have default-Windows support)
if (os.platform() === 'win32') {
	const ver = os.release().split('.').map(Number);
	if (!(ver[0] > 10 ||
		(ver[0] === 10 && ver[1] > 0) ||
		(ver[0] === 10 && ver[1] === 0 && ver[2] >= 15063))) {
		throw new Error("Noble UWP bindings require Windows >= 10.0.15063.");
	}

	const Noble = require('noble/lib/noble');
	const uwpBindings = require('./lib/bindings.js');
	const uwpAddition = require('./lib/uwpAddition.js');

	var nobleInstance = new Noble(uwpBindings);
	uwpAddition.init(nobleInstance._bindings);
	nobleInstance.uwp = uwpAddition;

	module.exports = nobleInstance;
} else {
	module.exports = require('noble');
}
