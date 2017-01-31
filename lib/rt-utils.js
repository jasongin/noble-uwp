'use strict';

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
  var a = new Array(o.length);
  for (var i = 0; i < a.length; i++) {
    a[i] = o[i];
  }
  return a;
}

// Convert a WinRT IMap to a JS Map.
function toMap(o) {
  var m = new Map();
  for (var i = o.first(); i.hasCurrent; i.moveNext()) {
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

module.exports = {
	using,
	promisify,
	toArray,
	toMap,
	toBuffer,
	fromBuffer,
};
