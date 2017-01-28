'use strict';

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

module.exports = {
	promisify,
	toArray,
	toMap,
};
