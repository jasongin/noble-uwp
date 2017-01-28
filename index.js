'use strict';

const os = require('os');

if (os.platform() === 'win32') {
	const ver = os.release().split('.').map(Number);
	if (!(ver[0] > 10 ||
			(ver[0] === 10 && ver[1] > 0) ||
			(ver[0] === 10 && ver[1] === 0 && ver[2] >= 15014))) {
		throw new Error("Noble UWP bindings require Windows >= 10.0.15014.");
	}

	const Noble = require('./node_modules/noble/lib/noble');
	const uwpBindings = require('./lib/bindings.js');
	module.exports = new Noble(uwpBindings);
} else {
	module.exports = require('noble');;
}
