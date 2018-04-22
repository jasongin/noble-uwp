'use strict';

// Utility functions for working with NodeRT projections.

const debug = require('debug')('noble-uwp');

// Relative path to NodeRT-generaged UWP namespace modules.
const uwpRoot = '../uwp/';

// Require a NodeRt namespace package and load it into the global namespace.
function using(ns) {
	let nsParts = ns.split('.');
	let parentObj = global;

	// Build an object tree as necessary for the namespace hierarchy.
	for (let i = 0; i < nsParts.length - 1; i++) {
		let nsObj = parentObj[nsParts[i]];
		if (!nsObj) {
			nsObj = {};
			parentObj[nsParts[i]] = nsObj;
		}
		parentObj = nsObj;
	}

	let lastNsPart = nsParts[nsParts.length - 1];
	let nsPackage = require(uwpRoot + ns.toLowerCase());

	// Merge in any already-loaded sub-namespaces.
	// This allows loading in non-hierarchical order.
	let nsObj = parentObj[lastNsPart];
	if (nsObj) {
		Object.keys(nsObj).forEach(key => {
			nsPackage[key] = nsObj[key];
		})
	}
	parentObj[lastNsPart] = nsPackage;
}

// Convert a NodeRT async method from callback to promise.
function promisify(fn, o) {
	return (...args) => {
		return new Promise((resolve, reject) => {
			(o ? fn.bind(o) : fn)(...args, (err, result) => {
				if (err) reject(err);
				else resolve(result);
			});
		});
	};
}

// Convert a WinRT IVectorView to a JS Array.
function toArray(o) {
	let a = new Array(o.length);
	for (let i = 0; i < a.length; i++) {
		a[i] = o[i];
	}
	return a;
}

// Convert a WinRT IMap to a JS Map.
function toMap(o) {
	let m = new Map();
	for (let i = o.first(); i.hasCurrent; i.moveNext()) {
		m.set(i.current.key, i.current.value);
	}
	return m;
}

// Convert a WinRT IBuffer to a JS Buffer.
function toBuffer(b) {
	// TODO: Use nodert-streams to more efficiently convert the buffer?
	let len = b.length;
	const DataReader = Windows.Storage.Streams.DataReader;
	let r = DataReader.fromBuffer(b);
	let a = new Uint8Array(len);
	for (let i = 0; i < len; i++) {
		a[i] = r.readByte();
	}
	return Buffer.from(a.buffer);
}

// Convert a JS Buffer to a WinRT IBuffer.
function fromBuffer(b) {
	// TODO: Use nodert-streams to more efficiently convert the buffer?
	let len = b.length;
	const DataWriter = Windows.Storage.Streams.DataWriter;
	let w = new DataWriter();
	for (let i = 0; i < len; i++) {
		w.writeByte(b[i]);
	}
	return w.detachBuffer();
}

let keepAliveIntervalId = 0;
let keepAliveIntervalCount = 0;

// Increment or decrement the count of WinRT async tasks.
// While the count is non-zero an interval is used to keep the JS engine alive.
function keepAlive(k) {
	if (k) {
		if (++keepAliveIntervalCount === 1) {
			// The actual duration doesn't really matter: it should be large but not too large.
			keepAliveIntervalId = setInterval(() => { }, 24 * 60 * 60 * 1000);
		}
	} else {
		if (--keepAliveIntervalCount === 0) {
			clearInterval(keepAliveIntervalId);
		}
	}
	debug(`keepAlive(${k}) => ${keepAliveIntervalCount}`);
}

const disposableMap = {};

function trackDisposable(key, obj) {
	if (!obj) {
		return obj;
	}

	if (typeof obj.close !== "function") {
		throw new Error('Object does not have a close function.');
	}

	let disposableList = disposableMap[key];

	if (!disposableList) {
		disposableList = [];
		disposableMap[key] = disposableList;
	}

	for (let i = 0; i < disposableList.length; i++) {
		const disposable = disposableList[i];
		if (Object.is(obj, disposable)) {
			return obj;
		}
	}

	disposableList.push(obj);
	return obj;
}

function trackDisposables(key, array) {
	array.forEach(obj => trackDisposable(key, obj));
	return array;
}

function disposeAll(key) {
	const disposableList = disposableMap[key];

	if (!disposableList) {
		return;
	}

	debug('Disposing %d objects for %s', disposableList.length, key);

	for (let i = 0; i < disposableList.length; i++) {
		const disposable = disposableList[i];
		disposable.close();
	}
}

module.exports = {
	using,
	promisify,
	toArray,
	toMap,
	toBuffer,
	fromBuffer,
	keepAlive,
	trackDisposable,
	trackDisposables,
	disposeAll,
};
