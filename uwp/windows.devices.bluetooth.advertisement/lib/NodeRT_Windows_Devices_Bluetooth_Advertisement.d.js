_BluetoothLEScanningMode = function () {
  this.passive = 0;
  this.active = 1;
}
exports.BluetoothLEScanningMode = new _BluetoothLEScanningMode();

_BluetoothLEAdvertisementFlags = function () {
  this.none = 0;
  this.limitedDiscoverableMode = 1;
  this.generalDiscoverableMode = 2;
  this.classicNotSupported = 3;
  this.dualModeControllerCapable = 4;
  this.dualModeHostCapable = 5;
}
exports.BluetoothLEAdvertisementFlags = new _BluetoothLEAdvertisementFlags();

_BluetoothLEAdvertisementType = function () {
  this.connectableUndirected = 0;
  this.connectableDirected = 1;
  this.scannableUndirected = 2;
  this.nonConnectableUndirected = 3;
  this.scanResponse = 4;
}
exports.BluetoothLEAdvertisementType = new _BluetoothLEAdvertisementType();

_BluetoothLEAdvertisementWatcherStatus = function () {
  this.created = 0;
  this.started = 1;
  this.stopping = 2;
  this.stopped = 3;
  this.aborted = 4;
}
exports.BluetoothLEAdvertisementWatcherStatus = new _BluetoothLEAdvertisementWatcherStatus();

_BluetoothLEAdvertisementPublisherStatus = function () {
  this.created = 0;
  this.waiting = 1;
  this.started = 2;
  this.stopping = 3;
  this.stopped = 4;
  this.aborted = 5;
}
exports.BluetoothLEAdvertisementPublisherStatus = new _BluetoothLEAdvertisementPublisherStatus();

BluetoothLEManufacturerData = (function () {
  var cls = function BluetoothLEManufacturerData() {
    this.data = new Object();
    this.companyId = new Number();
  };
  
var cls = function BluetoothLEManufacturerData(companyId, data) {
      this.data = new Object();
      this.companyId = new Number();
};


  return cls;
}) ();
exports.BluetoothLEManufacturerData = BluetoothLEManufacturerData;

BluetoothLEAdvertisementDataSection = (function () {
  var cls = function BluetoothLEAdvertisementDataSection() {
    this.dataType = new Number();
    this.data = new Object();
  };
  
var cls = function BluetoothLEAdvertisementDataSection(dataType, data) {
      this.dataType = new Number();
      this.data = new Object();
};


  return cls;
}) ();
exports.BluetoothLEAdvertisementDataSection = BluetoothLEAdvertisementDataSection;

BluetoothLEAdvertisement = (function () {
  var cls = function BluetoothLEAdvertisement() {
    this.localName = new String();
    this.flags = new BluetoothLEAdvertisementFlags();
    this.dataSections = new Object();
    this.manufacturerData = new Object();
    this.serviceUuids = new Object();
  };
  

  cls.prototype.getManufacturerDataByCompanyId = function getManufacturerDataByCompanyId(companyId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="companyId" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.getSectionsByType = function getSectionsByType(type) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="type" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.BluetoothLEAdvertisement = BluetoothLEAdvertisement;

BluetoothLEAdvertisementBytePattern = (function () {
  var cls = function BluetoothLEAdvertisementBytePattern() {
    this.offset = new Number();
    this.dataType = new Number();
    this.data = new Object();
  };
  
var cls = function BluetoothLEAdvertisementBytePattern(dataType, offset, data) {
      this.offset = new Number();
      this.dataType = new Number();
      this.data = new Object();
};


  return cls;
}) ();
exports.BluetoothLEAdvertisementBytePattern = BluetoothLEAdvertisementBytePattern;

BluetoothLEAdvertisementFilter = (function () {
  var cls = function BluetoothLEAdvertisementFilter() {
    this.advertisement = new BluetoothLEAdvertisement();
    this.bytePatterns = new Object();
  };
  

  return cls;
}) ();
exports.BluetoothLEAdvertisementFilter = BluetoothLEAdvertisementFilter;

BluetoothLEAdvertisementWatcherStoppedEventArgs = (function () {
  var cls = function BluetoothLEAdvertisementWatcherStoppedEventArgs() {
    this.error = new Number();
  };
  

  return cls;
}) ();
exports.BluetoothLEAdvertisementWatcherStoppedEventArgs = BluetoothLEAdvertisementWatcherStoppedEventArgs;

BluetoothLEAdvertisementWatcher = (function () {
  var cls = function BluetoothLEAdvertisementWatcher() {
    this.signalStrengthFilter = new Object();
    this.scanningMode = new BluetoothLEScanningMode();
    this.advertisementFilter = new BluetoothLEAdvertisementFilter();
    this.maxOutOfRangeTimeout = new Number();
    this.maxSamplingInterval = new Number();
    this.minOutOfRangeTimeout = new Number();
    this.minSamplingInterval = new Number();
    this.status = new BluetoothLEAdvertisementWatcherStatus();
  };
  
var cls = function BluetoothLEAdvertisementWatcher(advertisementFilter) {
      this.signalStrengthFilter = new Object();
      this.scanningMode = new BluetoothLEScanningMode();
      this.advertisementFilter = new BluetoothLEAdvertisementFilter();
      this.maxOutOfRangeTimeout = new Number();
      this.maxSamplingInterval = new Number();
      this.minOutOfRangeTimeout = new Number();
      this.minSamplingInterval = new Number();
      this.status = new BluetoothLEAdvertisementWatcherStatus();
};


  cls.prototype.start = function start() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.stop = function stop() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.BluetoothLEAdvertisementWatcher = BluetoothLEAdvertisementWatcher;

BluetoothLEAdvertisementReceivedEventArgs = (function () {
  var cls = function BluetoothLEAdvertisementReceivedEventArgs() {
    this.advertisement = new BluetoothLEAdvertisement();
    this.advertisementType = new BluetoothLEAdvertisementType();
    this.bluetoothAddress = new Number();
    this.rawSignalStrengthInDBm = new Number();
    this.timestamp = new Date();
  };
  

  return cls;
}) ();
exports.BluetoothLEAdvertisementReceivedEventArgs = BluetoothLEAdvertisementReceivedEventArgs;

BluetoothLEAdvertisementDataTypes = (function () {
  var cls = function BluetoothLEAdvertisementDataTypes() {
  };
  

  cls.advertisingInterval = new Number();
  cls.appearance = new Number();
  cls.completeLocalName = new Number();
  cls.completeService128BitUuids = new Number();
  cls.completeService16BitUuids = new Number();
  cls.completeService32BitUuids = new Number();
  cls.flags = new Number();
  cls.incompleteService128BitUuids = new Number();
  cls.incompleteService16BitUuids = new Number();
  cls.incompleteService32BitUuids = new Number();
  cls.manufacturerSpecificData = new Number();
  cls.publicTargetAddress = new Number();
  cls.randomTargetAddress = new Number();
  cls.serviceData128BitUuids = new Number();
  cls.serviceData16BitUuids = new Number();
  cls.serviceData32BitUuids = new Number();
  cls.serviceSolicitation128BitUuids = new Number();
  cls.serviceSolicitation16BitUuids = new Number();
  cls.serviceSolicitation32BitUuids = new Number();
  cls.shortenedLocalName = new Number();
  cls.slaveConnectionIntervalRange = new Number();
  cls.txPowerLevel = new Number();
  return cls;
}) ();
exports.BluetoothLEAdvertisementDataTypes = BluetoothLEAdvertisementDataTypes;

BluetoothLEAdvertisementPublisherStatusChangedEventArgs = (function () {
  var cls = function BluetoothLEAdvertisementPublisherStatusChangedEventArgs() {
    this.error = new Number();
    this.status = new BluetoothLEAdvertisementPublisherStatus();
  };
  

  return cls;
}) ();
exports.BluetoothLEAdvertisementPublisherStatusChangedEventArgs = BluetoothLEAdvertisementPublisherStatusChangedEventArgs;

BluetoothLEAdvertisementPublisher = (function () {
  var cls = function BluetoothLEAdvertisementPublisher() {
    this.advertisement = new BluetoothLEAdvertisement();
    this.status = new BluetoothLEAdvertisementPublisherStatus();
  };
  
var cls = function BluetoothLEAdvertisementPublisher(advertisement) {
      this.advertisement = new BluetoothLEAdvertisement();
      this.status = new BluetoothLEAdvertisementPublisherStatus();
};


  cls.prototype.start = function start() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.stop = function stop() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.BluetoothLEAdvertisementPublisher = BluetoothLEAdvertisementPublisher;

