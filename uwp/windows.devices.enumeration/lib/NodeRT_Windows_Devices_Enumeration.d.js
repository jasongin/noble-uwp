  
Color = (function () {
  var cls = function Color() {
    };
  return cls;
}) ();
exports.Color = Color;


  
Rect = (function () {
  var cls = function Rect() {
    };
  return cls;
}) ();
exports.Rect = Rect;


_DevicePickerDisplayStatusOptions = function () {
  this.none = 0;
  this.showProgress = 1;
  this.showDisconnectButton = 2;
  this.showRetryButton = 3;
}
exports.DevicePickerDisplayStatusOptions = new _DevicePickerDisplayStatusOptions();

_DeviceClass = function () {
  this.all = 0;
  this.audioCapture = 1;
  this.audioRender = 2;
  this.portableStorageDevice = 3;
  this.videoCapture = 4;
  this.imageScanner = 5;
  this.location = 6;
}
exports.DeviceClass = new _DeviceClass();

_DeviceWatcherStatus = function () {
  this.created = 0;
  this.started = 1;
  this.enumerationCompleted = 2;
  this.stopping = 3;
  this.stopped = 4;
  this.aborted = 5;
}
exports.DeviceWatcherStatus = new _DeviceWatcherStatus();

_Panel = function () {
  this.unknown = 0;
  this.front = 1;
  this.back = 2;
  this.top = 3;
  this.bottom = 4;
  this.left = 5;
  this.right = 6;
}
exports.Panel = new _Panel();

_DeviceInformationKind = function () {
  this.unknown = 0;
  this.deviceInterface = 1;
  this.deviceContainer = 2;
  this.device = 3;
  this.deviceInterfaceClass = 4;
  this.associationEndpoint = 5;
  this.associationEndpointContainer = 6;
  this.associationEndpointService = 7;
}
exports.DeviceInformationKind = new _DeviceInformationKind();

_DeviceWatcherEventKind = function () {
  this.add = 0;
  this.update = 1;
  this.remove = 2;
}
exports.DeviceWatcherEventKind = new _DeviceWatcherEventKind();

_DevicePairingKinds = function () {
  this.none = 0;
  this.confirmOnly = 1;
  this.displayPin = 2;
  this.providePin = 3;
  this.confirmPinMatch = 4;
}
exports.DevicePairingKinds = new _DevicePairingKinds();

_DevicePairingResultStatus = function () {
  this.paired = 0;
  this.notReadyToPair = 1;
  this.notPaired = 2;
  this.alreadyPaired = 3;
  this.connectionRejected = 4;
  this.tooManyConnections = 5;
  this.hardwareFailure = 6;
  this.authenticationTimeout = 7;
  this.authenticationNotAllowed = 8;
  this.authenticationFailure = 9;
  this.noSupportedProfiles = 10;
  this.protectionLevelCouldNotBeMet = 11;
  this.accessDenied = 12;
  this.invalidCeremonyData = 13;
  this.pairingCanceled = 14;
  this.operationAlreadyInProgress = 15;
  this.requiredHandlerNotRegistered = 16;
  this.rejectedByHandler = 17;
  this.remoteDeviceHasAssociation = 18;
  this.failed = 19;
}
exports.DevicePairingResultStatus = new _DevicePairingResultStatus();

_DeviceUnpairingResultStatus = function () {
  this.unpaired = 0;
  this.alreadyUnpaired = 1;
  this.operationAlreadyInProgress = 2;
  this.accessDenied = 3;
  this.failed = 4;
}
exports.DeviceUnpairingResultStatus = new _DeviceUnpairingResultStatus();

_DevicePairingProtectionLevel = function () {
  this.default = 0;
  this.none = 1;
  this.encryption = 2;
  this.encryptionAndAuthentication = 3;
}
exports.DevicePairingProtectionLevel = new _DevicePairingProtectionLevel();

_DeviceAccessStatus = function () {
  this.unspecified = 0;
  this.allowed = 1;
  this.deniedByUser = 2;
  this.deniedBySystem = 3;
}
exports.DeviceAccessStatus = new _DeviceAccessStatus();

DeviceConnectionChangeTriggerDetails = (function () {
  var cls = function DeviceConnectionChangeTriggerDetails() {
    this.deviceId = new String();
  };
  

  return cls;
}) ();
exports.DeviceConnectionChangeTriggerDetails = DeviceConnectionChangeTriggerDetails;

DevicePickerAppearance = (function () {
  var cls = function DevicePickerAppearance() {
    this.title = new String();
    this.selectedForegroundColor = new Object();
    this.selectedBackgroundColor = new Object();
    this.selectedAccentColor = new Object();
    this.foregroundColor = new Object();
    this.backgroundColor = new Object();
    this.accentColor = new Object();
  };
  

  return cls;
}) ();
exports.DevicePickerAppearance = DevicePickerAppearance;

DeviceSelectedEventArgs = (function () {
  var cls = function DeviceSelectedEventArgs() {
    this.selectedDevice = new DeviceInformation();
  };
  

  return cls;
}) ();
exports.DeviceSelectedEventArgs = DeviceSelectedEventArgs;

DeviceDisconnectButtonClickedEventArgs = (function () {
  var cls = function DeviceDisconnectButtonClickedEventArgs() {
    this.device = new DeviceInformation();
  };
  

  return cls;
}) ();
exports.DeviceDisconnectButtonClickedEventArgs = DeviceDisconnectButtonClickedEventArgs;

DevicePickerFilter = (function () {
  var cls = function DevicePickerFilter() {
    this.supportedDeviceClasses = new Object();
    this.supportedDeviceSelectors = new Object();
  };
  

  return cls;
}) ();
exports.DevicePickerFilter = DevicePickerFilter;

DevicePicker = (function () {
  var cls = function DevicePicker() {
    this.appearance = new DevicePickerAppearance();
    this.filter = new DevicePickerFilter();
    this.requestedProperties = new Object();
  };
  

  cls.prototype.pickSingleDeviceAsync = function pickSingleDeviceAsync(selection, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="selection" type="Object">A param.</param>
    /// </signature>
  }

cls.prototype.pickSingleDeviceAsync = function pickSingleDeviceAsync(selection, placement, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="selection" type="Object">A param.</param>
    /// <param name="placement" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.show = function show(selection) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="selection" type="Object">A param.</param>
    /// </signature>
  }

cls.prototype.show = function show(selection, placement) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="selection" type="Object">A param.</param>
    /// <param name="placement" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.hide = function hide() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.setDisplayStatus = function setDisplayStatus(device, status, options) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="device" type="DeviceInformation">A param.</param>
    /// <param name="status" type="String">A param.</param>
    /// <param name="options" type="DevicePickerDisplayStatusOptions">A param.</param>
    /// </signature>
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.DevicePicker = DevicePicker;

DeviceThumbnail = (function () {
  var cls = function DeviceThumbnail() {
    this.contentType = new String();
    this.size = new Number();
    this.canRead = new Boolean();
    this.canWrite = new Boolean();
    this.position = new Number();
  };
  

  cls.prototype.readAsync = function readAsync(buffer, count, options, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="Object">A param.</param>
    /// <param name="count" type="Number">A param.</param>
    /// <param name="options" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeAsync = function writeAsync(buffer, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.flushAsync = function flushAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.getInputStreamAt = function getInputStreamAt(position) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="position" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.getOutputStreamAt = function getOutputStreamAt(position) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="position" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.seek = function seek(position) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="position" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.cloneStream = function cloneStream() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.close = function close() {
}


  return cls;
}) ();
exports.DeviceThumbnail = DeviceThumbnail;

EnclosureLocation = (function () {
  var cls = function EnclosureLocation() {
    this.inDock = new Boolean();
    this.inLid = new Boolean();
    this.panel = new Panel();
    this.rotationAngleInDegreesClockwise = new Number();
  };
  

  return cls;
}) ();
exports.EnclosureLocation = EnclosureLocation;

DeviceInformationUpdate = (function () {
  var cls = function DeviceInformationUpdate() {
    this.id = new String();
    this.properties = new Object();
    this.kind = new DeviceInformationKind();
  };
  

  return cls;
}) ();
exports.DeviceInformationUpdate = DeviceInformationUpdate;

DeviceInformationCollection = (function () {
  var cls = function DeviceInformationCollection() {
  };
  

  cls.prototype.getAt = function getAt(index) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="index" type="Number">A param.</param>
    /// <returns type="DeviceInformation" />
    /// </signature>
    return new DeviceInformation();
  }


  cls.prototype.indexOf = function indexOf(value, index) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="DeviceInformation">A param.</param>
    /// <param name="index" type="Number">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  cls.prototype.getMany = function () {
}

  cls.prototype.first = function first() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.DeviceInformationCollection = DeviceInformationCollection;

DeviceWatcher = (function () {
  var cls = function DeviceWatcher() {
    this.status = new DeviceWatcherStatus();
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


  cls.prototype.getBackgroundTrigger = function getBackgroundTrigger(requestedEventKinds) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="requestedEventKinds" type="Object">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.DeviceWatcher = DeviceWatcher;

DeviceInformation = (function () {
  var cls = function DeviceInformation() {
    this.enclosureLocation = new EnclosureLocation();
    this.id = new String();
    this.isDefault = new Boolean();
    this.isEnabled = new Boolean();
    this.name = new String();
    this.properties = new Object();
    this.kind = new DeviceInformationKind();
    this.pairing = new DeviceInformationPairing();
  };
  

  cls.prototype.getThumbnailAsync = function getThumbnailAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.getGlyphThumbnailAsync = function getGlyphThumbnailAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.update = function update(updateInfo) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="updateInfo" type="DeviceInformationUpdate">A param.</param>
    /// </signature>
  }


  cls.createFromIdAsync = function createFromIdAsync(deviceId, additionalProperties, kind, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="deviceId" type="String">A param.</param>
    /// <param name="additionalProperties" type="Object">A param.</param>
    /// <param name="kind" type="DeviceInformationKind">A param.</param>
    /// </signature>
  }

cls.createFromIdAsync = function createFromIdAsync(deviceId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="deviceId" type="String">A param.</param>
    /// </signature>
  }

cls.createFromIdAsync = function createFromIdAsync(deviceId, additionalProperties, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="deviceId" type="String">A param.</param>
    /// <param name="additionalProperties" type="Object">A param.</param>
    /// </signature>
  }



  cls.findAllAsync = function findAllAsync(aqsFilter, additionalProperties, kind, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="aqsFilter" type="String">A param.</param>
    /// <param name="additionalProperties" type="Object">A param.</param>
    /// <param name="kind" type="DeviceInformationKind">A param.</param>
    /// </signature>
  }

cls.findAllAsync = function findAllAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.findAllAsync = function findAllAsync(deviceClass, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="deviceClass" type="DeviceClass">A param.</param>
    /// </signature>
  }

cls.findAllAsync = function findAllAsync(aqsFilter, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="aqsFilter" type="String">A param.</param>
    /// </signature>
  }

cls.findAllAsync = function findAllAsync(aqsFilter, additionalProperties, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="aqsFilter" type="String">A param.</param>
    /// <param name="additionalProperties" type="Object">A param.</param>
    /// </signature>
  }



  cls.getAqsFilterFromDeviceClass = function getAqsFilterFromDeviceClass(deviceClass) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="deviceClass" type="DeviceClass">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.createWatcher = function createWatcher(aqsFilter, additionalProperties, kind) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="aqsFilter" type="String">A param.</param>
    /// <param name="additionalProperties" type="Object">A param.</param>
    /// <param name="kind" type="DeviceInformationKind">A param.</param>
    /// <returns type="DeviceWatcher" />
    /// </signature>
    return new DeviceWatcher();
  }

cls.createWatcher = function createWatcher() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="DeviceWatcher" />
    /// </signature>
    return new DeviceWatcher();
  }

cls.createWatcher = function createWatcher(deviceClass) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="deviceClass" type="DeviceClass">A param.</param>
    /// <returns type="DeviceWatcher" />
    /// </signature>
    return new DeviceWatcher();
  }

cls.createWatcher = function createWatcher(aqsFilter) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="aqsFilter" type="String">A param.</param>
    /// <returns type="DeviceWatcher" />
    /// </signature>
    return new DeviceWatcher();
  }

cls.createWatcher = function createWatcher(aqsFilter, additionalProperties) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="aqsFilter" type="String">A param.</param>
    /// <param name="additionalProperties" type="Object">A param.</param>
    /// <returns type="DeviceWatcher" />
    /// </signature>
    return new DeviceWatcher();
  }


  return cls;
}) ();
exports.DeviceInformation = DeviceInformation;

DevicePairingResult = (function () {
  var cls = function DevicePairingResult() {
    this.protectionLevelUsed = new DevicePairingProtectionLevel();
    this.status = new DevicePairingResultStatus();
  };
  

  return cls;
}) ();
exports.DevicePairingResult = DevicePairingResult;

DeviceUnpairingResult = (function () {
  var cls = function DeviceUnpairingResult() {
    this.status = new DeviceUnpairingResultStatus();
  };
  

  return cls;
}) ();
exports.DeviceUnpairingResult = DeviceUnpairingResult;

IDevicePairingSettings = (function () {
  var cls = function IDevicePairingSettings() {
  };
  

  return cls;
}) ();
exports.IDevicePairingSettings = IDevicePairingSettings;

DevicePairingRequestedEventArgs = (function () {
  var cls = function DevicePairingRequestedEventArgs() {
    this.deviceInformation = new DeviceInformation();
    this.pairingKind = new DevicePairingKinds();
    this.pin = new String();
  };
  

  cls.prototype.accept = function accept() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.accept = function accept(pin) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="pin" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.getDeferral = function getDeferral() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.DevicePairingRequestedEventArgs = DevicePairingRequestedEventArgs;

DeviceInformationCustomPairing = (function () {
  var cls = function DeviceInformationCustomPairing() {
  };
  

  cls.prototype.pairAsync = function pairAsync(pairingKindsSupported, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="pairingKindsSupported" type="DevicePairingKinds">A param.</param>
    /// </signature>
  }

cls.prototype.pairAsync = function pairAsync(pairingKindsSupported, minProtectionLevel, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="pairingKindsSupported" type="DevicePairingKinds">A param.</param>
    /// <param name="minProtectionLevel" type="DevicePairingProtectionLevel">A param.</param>
    /// </signature>
  }

cls.prototype.pairAsync = function pairAsync(pairingKindsSupported, minProtectionLevel, devicePairingSettings, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="pairingKindsSupported" type="DevicePairingKinds">A param.</param>
    /// <param name="minProtectionLevel" type="DevicePairingProtectionLevel">A param.</param>
    /// <param name="devicePairingSettings" type="IDevicePairingSettings">A param.</param>
    /// </signature>
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.DeviceInformationCustomPairing = DeviceInformationCustomPairing;

DeviceInformationPairing = (function () {
  var cls = function DeviceInformationPairing() {
    this.canPair = new Boolean();
    this.isPaired = new Boolean();
    this.custom = new DeviceInformationCustomPairing();
    this.protectionLevel = new DevicePairingProtectionLevel();
  };
  

  cls.prototype.pairAsync = function pairAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.pairAsync = function pairAsync(minProtectionLevel, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="minProtectionLevel" type="DevicePairingProtectionLevel">A param.</param>
    /// </signature>
  }

cls.prototype.pairAsync = function pairAsync(minProtectionLevel, devicePairingSettings, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="minProtectionLevel" type="DevicePairingProtectionLevel">A param.</param>
    /// <param name="devicePairingSettings" type="IDevicePairingSettings">A param.</param>
    /// </signature>
  }


  cls.prototype.unpairAsync = function unpairAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.tryRegisterForAllInboundPairingRequests = function tryRegisterForAllInboundPairingRequests(pairingKindsSupported) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="pairingKindsSupported" type="DevicePairingKinds">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  return cls;
}) ();
exports.DeviceInformationPairing = DeviceInformationPairing;

DeviceAccessChangedEventArgs = (function () {
  var cls = function DeviceAccessChangedEventArgs() {
    this.status = new DeviceAccessStatus();
    this.id = new String();
  };
  

  return cls;
}) ();
exports.DeviceAccessChangedEventArgs = DeviceAccessChangedEventArgs;

DeviceAccessInformation = (function () {
  var cls = function DeviceAccessInformation() {
    this.currentStatus = new DeviceAccessStatus();
  };
  

  cls.createFromId = function createFromId(deviceId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="deviceId" type="String">A param.</param>
    /// <returns type="DeviceAccessInformation" />
    /// </signature>
    return new DeviceAccessInformation();
  }


  cls.createFromDeviceClassId = function createFromDeviceClassId(deviceClassId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="deviceClassId" type="String">A param.</param>
    /// <returns type="DeviceAccessInformation" />
    /// </signature>
    return new DeviceAccessInformation();
  }


  cls.createFromDeviceClass = function createFromDeviceClass(deviceClass) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="deviceClass" type="DeviceClass">A param.</param>
    /// <returns type="DeviceAccessInformation" />
    /// </signature>
    return new DeviceAccessInformation();
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.DeviceAccessInformation = DeviceAccessInformation;

DeviceWatcherEvent = (function () {
  var cls = function DeviceWatcherEvent() {
    this.deviceInformation = new DeviceInformation();
    this.deviceInformationUpdate = new DeviceInformationUpdate();
    this.kind = new DeviceWatcherEventKind();
  };
  

  return cls;
}) ();
exports.DeviceWatcherEvent = DeviceWatcherEvent;

DeviceWatcherTriggerDetails = (function () {
  var cls = function DeviceWatcherTriggerDetails() {
    this.deviceWatcherEvents = new Object();
  };
  

  return cls;
}) ();
exports.DeviceWatcherTriggerDetails = DeviceWatcherTriggerDetails;

