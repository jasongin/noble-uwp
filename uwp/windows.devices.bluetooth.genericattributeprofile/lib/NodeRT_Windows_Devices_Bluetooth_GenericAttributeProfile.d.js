_GattSessionStatus = function () {
  this.closed = 0;
  this.active = 1;
}
exports.GattSessionStatus = new _GattSessionStatus();

_GattCharacteristicProperties = function () {
  this.none = 0;
  this.broadcast = 1;
  this.read = 2;
  this.writeWithoutResponse = 3;
  this.write = 4;
  this.notify = 5;
  this.indicate = 6;
  this.authenticatedSignedWrites = 7;
  this.extendedProperties = 8;
  this.reliableWrites = 9;
  this.writableAuxiliaries = 10;
}
exports.GattCharacteristicProperties = new _GattCharacteristicProperties();

_GattClientCharacteristicConfigurationDescriptorValue = function () {
  this.none = 0;
  this.notify = 1;
  this.indicate = 2;
}
exports.GattClientCharacteristicConfigurationDescriptorValue = new _GattClientCharacteristicConfigurationDescriptorValue();

_GattProtectionLevel = function () {
  this.plain = 0;
  this.authenticationRequired = 1;
  this.encryptionRequired = 2;
  this.encryptionAndAuthenticationRequired = 3;
}
exports.GattProtectionLevel = new _GattProtectionLevel();

_GattWriteOption = function () {
  this.writeWithResponse = 0;
  this.writeWithoutResponse = 1;
}
exports.GattWriteOption = new _GattWriteOption();

_GattCommunicationStatus = function () {
  this.success = 0;
  this.unreachable = 1;
  this.protocolError = 2;
  this.accessDenied = 3;
}
exports.GattCommunicationStatus = new _GattCommunicationStatus();

_GattSharingMode = function () {
  this.unspecified = 0;
  this.exclusive = 1;
  this.sharedReadOnly = 2;
  this.sharedReadAndWrite = 3;
}
exports.GattSharingMode = new _GattSharingMode();

_GattOpenStatus = function () {
  this.unspecified = 0;
  this.success = 1;
  this.alreadyOpened = 2;
  this.notFound = 3;
  this.sharingViolation = 4;
  this.accessDenied = 5;
}
exports.GattOpenStatus = new _GattOpenStatus();

_GattRequestState = function () {
  this.pending = 0;
  this.completed = 1;
  this.canceled = 2;
}
exports.GattRequestState = new _GattRequestState();

_GattServiceProviderAdvertisementStatus = function () {
  this.created = 0;
  this.stopped = 1;
  this.started = 2;
  this.aborted = 3;
}
exports.GattServiceProviderAdvertisementStatus = new _GattServiceProviderAdvertisementStatus();

GattDeviceService = (function () {
  var cls = function GattDeviceService() {
    this.attributeHandle = new Number();
    this.deviceId = new String();
    this.uuid = new String();
    this.device = new Object();
    this.parentServices = new Object();
    this.deviceAccessInformation = new Object();
    this.session = new GattSession();
    this.sharingMode = new GattSharingMode();
  };
  

  cls.prototype.requestAccessAsync = function requestAccessAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.openAsync = function openAsync(sharingMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="sharingMode" type="GattSharingMode">A param.</param>
    /// </signature>
  }


  cls.prototype.getCharacteristicsAsync = function getCharacteristicsAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.getCharacteristicsAsync = function getCharacteristicsAsync(cacheMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="cacheMode" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.getCharacteristicsForUuidAsync = function getCharacteristicsForUuidAsync(characteristicUuid, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="characteristicUuid" type="String">A param.</param>
    /// </signature>
  }

cls.prototype.getCharacteristicsForUuidAsync = function getCharacteristicsForUuidAsync(characteristicUuid, cacheMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="characteristicUuid" type="String">A param.</param>
    /// <param name="cacheMode" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.getIncludedServicesAsync = function getIncludedServicesAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.getIncludedServicesAsync = function getIncludedServicesAsync(cacheMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="cacheMode" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.getIncludedServicesForUuidAsync = function getIncludedServicesForUuidAsync(serviceUuid, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="serviceUuid" type="String">A param.</param>
    /// </signature>
  }

cls.prototype.getIncludedServicesForUuidAsync = function getIncludedServicesForUuidAsync(serviceUuid, cacheMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="serviceUuid" type="String">A param.</param>
    /// <param name="cacheMode" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.getCharacteristics = function getCharacteristics(characteristicUuid) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="characteristicUuid" type="String">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.getIncludedServices = function getIncludedServices(serviceUuid) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="serviceUuid" type="String">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.close = function close() {
}


  cls.prototype.getAllCharacteristics = function getAllCharacteristics() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.getAllIncludedServices = function getAllIncludedServices() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.fromIdAsync = function fromIdAsync(deviceId, sharingMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="deviceId" type="String">A param.</param>
    /// <param name="sharingMode" type="GattSharingMode">A param.</param>
    /// </signature>
  }

cls.fromIdAsync = function fromIdAsync(deviceId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="deviceId" type="String">A param.</param>
    /// </signature>
  }



  cls.getDeviceSelectorForBluetoothDeviceId = function getDeviceSelectorForBluetoothDeviceId(bluetoothDeviceId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="bluetoothDeviceId" type="Object">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }

cls.getDeviceSelectorForBluetoothDeviceId = function getDeviceSelectorForBluetoothDeviceId(bluetoothDeviceId, cacheMode) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="bluetoothDeviceId" type="Object">A param.</param>
    /// <param name="cacheMode" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.getDeviceSelectorForBluetoothDeviceIdAndUuid = function getDeviceSelectorForBluetoothDeviceIdAndUuid(bluetoothDeviceId, serviceUuid) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="bluetoothDeviceId" type="Object">A param.</param>
    /// <param name="serviceUuid" type="String">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }

cls.getDeviceSelectorForBluetoothDeviceIdAndUuid = function getDeviceSelectorForBluetoothDeviceIdAndUuid(bluetoothDeviceId, serviceUuid, cacheMode) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="bluetoothDeviceId" type="Object">A param.</param>
    /// <param name="serviceUuid" type="String">A param.</param>
    /// <param name="cacheMode" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.getDeviceSelectorFromUuid = function getDeviceSelectorFromUuid(serviceUuid) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="serviceUuid" type="String">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.getDeviceSelectorFromShortId = function getDeviceSelectorFromShortId(serviceShortId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="serviceShortId" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.convertShortIdToUuid = function convertShortIdToUuid(shortId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="shortId" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  return cls;
}) ();
exports.GattDeviceService = GattDeviceService;

GattDeviceServicesResult = (function () {
  var cls = function GattDeviceServicesResult() {
    this.protocolError = new Number();
    this.services = new Object();
    this.status = new GattCommunicationStatus();
  };
  

  return cls;
}) ();
exports.GattDeviceServicesResult = GattDeviceServicesResult;

GattProtocolError = (function () {
  var cls = function GattProtocolError() {
  };
  

  cls.attributeNotFound = new Number();
  cls.attributeNotLong = new Number();
  cls.insufficientAuthentication = new Number();
  cls.insufficientAuthorization = new Number();
  cls.insufficientEncryption = new Number();
  cls.insufficientEncryptionKeySize = new Number();
  cls.insufficientResources = new Number();
  cls.invalidAttributeValueLength = new Number();
  cls.invalidHandle = new Number();
  cls.invalidOffset = new Number();
  cls.invalidPdu = new Number();
  cls.prepareQueueFull = new Number();
  cls.readNotPermitted = new Number();
  cls.requestNotSupported = new Number();
  cls.unlikelyError = new Number();
  cls.unsupportedGroupType = new Number();
  cls.writeNotPermitted = new Number();
  return cls;
}) ();
exports.GattProtocolError = GattProtocolError;

GattSession = (function () {
  var cls = function GattSession() {
    this.maintainConnection = new Boolean();
    this.canMaintainConnection = new Boolean();
    this.deviceId = new Object();
    this.maxPduSize = new Number();
    this.sessionStatus = new GattSessionStatus();
  };
  

  cls.prototype.close = function close() {
}


  cls.fromDeviceIdAsync = function fromDeviceIdAsync(deviceId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="deviceId" type="Object">A param.</param>
    /// </signature>
  }



    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.GattSession = GattSession;

GattSessionStatusChangedEventArgs = (function () {
  var cls = function GattSessionStatusChangedEventArgs() {
    this.error = new Number();
    this.status = new GattSessionStatus();
  };
  

  return cls;
}) ();
exports.GattSessionStatusChangedEventArgs = GattSessionStatusChangedEventArgs;

GattCharacteristic = (function () {
  var cls = function GattCharacteristic() {
    this.protectionLevel = new GattProtectionLevel();
    this.attributeHandle = new Number();
    this.characteristicProperties = new GattCharacteristicProperties();
    this.presentationFormats = new Object();
    this.userDescription = new String();
    this.uuid = new String();
    this.service = new GattDeviceService();
  };
  

  cls.prototype.readValueAsync = function readValueAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.readValueAsync = function readValueAsync(cacheMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="cacheMode" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeValueAsync = function writeValueAsync(value, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// </signature>
  }

cls.prototype.writeValueAsync = function writeValueAsync(value, writeOption, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// <param name="writeOption" type="GattWriteOption">A param.</param>
    /// </signature>
  }


  cls.prototype.readClientCharacteristicConfigurationDescriptorAsync = function readClientCharacteristicConfigurationDescriptorAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.writeClientCharacteristicConfigurationDescriptorAsync = function writeClientCharacteristicConfigurationDescriptorAsync(clientCharacteristicConfigurationDescriptorValue, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="clientCharacteristicConfigurationDescriptorValue" type="GattClientCharacteristicConfigurationDescriptorValue">A param.</param>
    /// </signature>
  }


  cls.prototype.getDescriptorsAsync = function getDescriptorsAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.getDescriptorsAsync = function getDescriptorsAsync(cacheMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="cacheMode" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.getDescriptorsForUuidAsync = function getDescriptorsForUuidAsync(descriptorUuid, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="descriptorUuid" type="String">A param.</param>
    /// </signature>
  }

cls.prototype.getDescriptorsForUuidAsync = function getDescriptorsForUuidAsync(descriptorUuid, cacheMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="descriptorUuid" type="String">A param.</param>
    /// <param name="cacheMode" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeValueWithResultAsync = function writeValueWithResultAsync(value, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// </signature>
  }

cls.prototype.writeValueWithResultAsync = function writeValueWithResultAsync(value, writeOption, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// <param name="writeOption" type="GattWriteOption">A param.</param>
    /// </signature>
  }


  cls.prototype.writeClientCharacteristicConfigurationDescriptorWithResultAsync = function writeClientCharacteristicConfigurationDescriptorWithResultAsync(clientCharacteristicConfigurationDescriptorValue, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="clientCharacteristicConfigurationDescriptorValue" type="GattClientCharacteristicConfigurationDescriptorValue">A param.</param>
    /// </signature>
  }


  cls.prototype.getDescriptors = function getDescriptors(descriptorUuid) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="descriptorUuid" type="String">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.getAllDescriptors = function getAllDescriptors() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.convertShortIdToUuid = function convertShortIdToUuid(shortId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="shortId" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.GattCharacteristic = GattCharacteristic;

GattCharacteristicsResult = (function () {
  var cls = function GattCharacteristicsResult() {
    this.characteristics = new Object();
    this.protocolError = new Number();
    this.status = new GattCommunicationStatus();
  };
  

  return cls;
}) ();
exports.GattCharacteristicsResult = GattCharacteristicsResult;

GattDescriptor = (function () {
  var cls = function GattDescriptor() {
    this.protectionLevel = new GattProtectionLevel();
    this.attributeHandle = new Number();
    this.uuid = new String();
  };
  

  cls.prototype.readValueAsync = function readValueAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.readValueAsync = function readValueAsync(cacheMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="cacheMode" type="Number">A param.</param>
    /// </signature>
  }


  cls.prototype.writeValueAsync = function writeValueAsync(value, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.writeValueWithResultAsync = function writeValueWithResultAsync(value, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// </signature>
  }


  cls.convertShortIdToUuid = function convertShortIdToUuid(shortId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="shortId" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  return cls;
}) ();
exports.GattDescriptor = GattDescriptor;

GattPresentationFormat = (function () {
  var cls = function GattPresentationFormat() {
    this.description = new Number();
    this.exponent = new Number();
    this.formatType = new Number();
    this.namespace = new Number();
    this.unit = new Number();
  };
  

  cls.fromParts = function fromParts(formatType, exponent, unit, namespaceId, description) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="formatType" type="Number">A param.</param>
    /// <param name="exponent" type="Number">A param.</param>
    /// <param name="unit" type="Number">A param.</param>
    /// <param name="namespaceId" type="Number">A param.</param>
    /// <param name="description" type="Number">A param.</param>
    /// <returns type="GattPresentationFormat" />
    /// </signature>
    return new GattPresentationFormat();
  }


  cls.bluetoothSigAssignedNumbers = new Number();
  return cls;
}) ();
exports.GattPresentationFormat = GattPresentationFormat;

GattReadResult = (function () {
  var cls = function GattReadResult() {
    this.status = new GattCommunicationStatus();
    this.value = new Object();
    this.protocolError = new Number();
  };
  

  return cls;
}) ();
exports.GattReadResult = GattReadResult;

GattReadClientCharacteristicConfigurationDescriptorResult = (function () {
  var cls = function GattReadClientCharacteristicConfigurationDescriptorResult() {
    this.clientCharacteristicConfigurationDescriptor = new GattClientCharacteristicConfigurationDescriptorValue();
    this.status = new GattCommunicationStatus();
    this.protocolError = new Number();
  };
  

  return cls;
}) ();
exports.GattReadClientCharacteristicConfigurationDescriptorResult = GattReadClientCharacteristicConfigurationDescriptorResult;

GattValueChangedEventArgs = (function () {
  var cls = function GattValueChangedEventArgs() {
    this.characteristicValue = new Object();
    this.timestamp = new Date();
  };
  

  return cls;
}) ();
exports.GattValueChangedEventArgs = GattValueChangedEventArgs;

GattDescriptorsResult = (function () {
  var cls = function GattDescriptorsResult() {
    this.descriptors = new Object();
    this.protocolError = new Number();
    this.status = new GattCommunicationStatus();
  };
  

  return cls;
}) ();
exports.GattDescriptorsResult = GattDescriptorsResult;

GattWriteResult = (function () {
  var cls = function GattWriteResult() {
    this.protocolError = new Number();
    this.status = new GattCommunicationStatus();
  };
  

  return cls;
}) ();
exports.GattWriteResult = GattWriteResult;

GattPresentationFormatTypes = (function () {
  var cls = function GattPresentationFormatTypes() {
  };
  

  cls.bit2 = new Number();
  cls.boolean = new Number();
  cls.dUInt16 = new Number();
  cls.float = new Number();
  cls.float32 = new Number();
  cls.float64 = new Number();
  cls.nibble = new Number();
  cls.sFloat = new Number();
  cls.sInt12 = new Number();
  cls.sInt128 = new Number();
  cls.sInt16 = new Number();
  cls.sInt24 = new Number();
  cls.sInt32 = new Number();
  cls.sInt48 = new Number();
  cls.sInt64 = new Number();
  cls.sInt8 = new Number();
  cls.struct = new Number();
  cls.uInt12 = new Number();
  cls.uInt128 = new Number();
  cls.uInt16 = new Number();
  cls.uInt24 = new Number();
  cls.uInt32 = new Number();
  cls.uInt48 = new Number();
  cls.uInt64 = new Number();
  cls.uInt8 = new Number();
  cls.utf16 = new Number();
  cls.utf8 = new Number();
  return cls;
}) ();
exports.GattPresentationFormatTypes = GattPresentationFormatTypes;

GattServiceUuids = (function () {
  var cls = function GattServiceUuids() {
  };
  

  cls.cyclingSpeedAndCadence = new String();
  cls.battery = new String();
  cls.bloodPressure = new String();
  cls.genericAccess = new String();
  cls.genericAttribute = new String();
  cls.glucose = new String();
  cls.healthThermometer = new String();
  cls.heartRate = new String();
  cls.runningSpeedAndCadence = new String();
  cls.nextDstChange = new String();
  cls.alertNotification = new String();
  cls.currentTime = new String();
  cls.cyclingPower = new String();
  cls.deviceInformation = new String();
  cls.humanInterfaceDevice = new String();
  cls.immediateAlert = new String();
  cls.linkLoss = new String();
  cls.locationAndNavigation = new String();
  cls.phoneAlertStatus = new String();
  cls.referenceTimeUpdate = new String();
  cls.scanParameters = new String();
  cls.txPower = new String();
  return cls;
}) ();
exports.GattServiceUuids = GattServiceUuids;

GattCharacteristicUuids = (function () {
  var cls = function GattCharacteristicUuids() {
  };
  

  cls.batteryLevel = new String();
  cls.bloodPressureFeature = new String();
  cls.bloodPressureMeasurement = new String();
  cls.bodySensorLocation = new String();
  cls.cscFeature = new String();
  cls.cscMeasurement = new String();
  cls.glucoseFeature = new String();
  cls.glucoseMeasurement = new String();
  cls.glucoseMeasurementContext = new String();
  cls.heartRateControlPoint = new String();
  cls.heartRateMeasurement = new String();
  cls.intermediateCuffPressure = new String();
  cls.intermediateTemperature = new String();
  cls.measurementInterval = new String();
  cls.recordAccessControlPoint = new String();
  cls.rscFeature = new String();
  cls.rscMeasurement = new String();
  cls.sCControlPoint = new String();
  cls.sensorLocation = new String();
  cls.temperatureMeasurement = new String();
  cls.temperatureType = new String();
  cls.lnFeature = new String();
  cls.alertCategoryId = new String();
  cls.alertCategoryIdBitMask = new String();
  cls.alertLevel = new String();
  cls.alertNotificationControlPoint = new String();
  cls.alertStatus = new String();
  cls.bootKeyboardInputReport = new String();
  cls.bootKeyboardOutputReport = new String();
  cls.bootMouseInputReport = new String();
  cls.currentTime = new String();
  cls.cyclingPowerControlPoint = new String();
  cls.cyclingPowerFeature = new String();
  cls.cyclingPowerMeasurement = new String();
  cls.cyclingPowerVector = new String();
  cls.dateTime = new String();
  cls.dayDateTime = new String();
  cls.dayOfWeek = new String();
  cls.dstOffset = new String();
  cls.exactTime256 = new String();
  cls.firmwareRevisionString = new String();
  cls.gapAppearance = new String();
  cls.gapDeviceName = new String();
  cls.gapPeripheralPreferredConnectionParameters = new String();
  cls.gapPeripheralPrivacyFlag = new String();
  cls.gapReconnectionAddress = new String();
  cls.gattServiceChanged = new String();
  cls.hardwareRevisionString = new String();
  cls.hidControlPoint = new String();
  cls.hidInformation = new String();
  cls.ieee1107320601RegulatoryCertificationDataList = new String();
  cls.lnControlPoint = new String();
  cls.localTimeInformation = new String();
  cls.locationAndSpeed = new String();
  cls.manufacturerNameString = new String();
  cls.modelNumberString = new String();
  cls.navigation = new String();
  cls.newAlert = new String();
  cls.pnpId = new String();
  cls.positionQuality = new String();
  cls.protocolMode = new String();
  cls.referenceTimeInformation = new String();
  cls.report = new String();
  cls.reportMap = new String();
  cls.ringerControlPoint = new String();
  cls.ringerSetting = new String();
  cls.scanIntervalWindow = new String();
  cls.scanRefresh = new String();
  cls.serialNumberString = new String();
  cls.softwareRevisionString = new String();
  cls.supportUnreadAlertCategory = new String();
  cls.supportedNewAlertCategory = new String();
  cls.systemId = new String();
  cls.timeAccuracy = new String();
  cls.timeSource = new String();
  cls.timeUpdateControlPoint = new String();
  cls.timeUpdateState = new String();
  cls.timeWithDst = new String();
  cls.timeZone = new String();
  cls.txPowerLevel = new String();
  cls.unreadAlertStatus = new String();
  return cls;
}) ();
exports.GattCharacteristicUuids = GattCharacteristicUuids;

GattDescriptorUuids = (function () {
  var cls = function GattDescriptorUuids() {
  };
  

  cls.characteristicAggregateFormat = new String();
  cls.characteristicExtendedProperties = new String();
  cls.characteristicPresentationFormat = new String();
  cls.characteristicUserDescription = new String();
  cls.clientCharacteristicConfiguration = new String();
  cls.serverCharacteristicConfiguration = new String();
  return cls;
}) ();
exports.GattDescriptorUuids = GattDescriptorUuids;

GattReliableWriteTransaction = (function () {
  var cls = function GattReliableWriteTransaction() {
  };
  

  cls.prototype.commitAsync = function commitAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.commitWithResultAsync = function commitWithResultAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.writeValue = function writeValue(characteristic, value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="characteristic" type="GattCharacteristic">A param.</param>
    /// <param name="value" type="Object">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.GattReliableWriteTransaction = GattReliableWriteTransaction;

GattServiceProviderAdvertisingParameters = (function () {
  var cls = function GattServiceProviderAdvertisingParameters() {
    this.isDiscoverable = new Boolean();
    this.isConnectable = new Boolean();
  };
  

  return cls;
}) ();
exports.GattServiceProviderAdvertisingParameters = GattServiceProviderAdvertisingParameters;

GattLocalCharacteristicParameters = (function () {
  var cls = function GattLocalCharacteristicParameters() {
    this.writeProtectionLevel = new GattProtectionLevel();
    this.userDescription = new String();
    this.staticValue = new Object();
    this.readProtectionLevel = new GattProtectionLevel();
    this.characteristicProperties = new GattCharacteristicProperties();
    this.presentationFormats = new Object();
  };
  

  return cls;
}) ();
exports.GattLocalCharacteristicParameters = GattLocalCharacteristicParameters;

GattLocalDescriptorParameters = (function () {
  var cls = function GattLocalDescriptorParameters() {
    this.writeProtectionLevel = new GattProtectionLevel();
    this.staticValue = new Object();
    this.readProtectionLevel = new GattProtectionLevel();
  };
  

  return cls;
}) ();
exports.GattLocalDescriptorParameters = GattLocalDescriptorParameters;

GattServiceProviderResult = (function () {
  var cls = function GattServiceProviderResult() {
    this.error = new Number();
    this.serviceProvider = new GattServiceProvider();
  };
  

  return cls;
}) ();
exports.GattServiceProviderResult = GattServiceProviderResult;

GattLocalService = (function () {
  var cls = function GattLocalService() {
    this.characteristics = new Object();
    this.uuid = new String();
  };
  

  cls.prototype.createCharacteristicAsync = function createCharacteristicAsync(characteristicUuid, parameters, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="characteristicUuid" type="String">A param.</param>
    /// <param name="parameters" type="GattLocalCharacteristicParameters">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.GattLocalService = GattLocalService;

GattServiceProvider = (function () {
  var cls = function GattServiceProvider() {
    this.advertisementStatus = new GattServiceProviderAdvertisementStatus();
    this.service = new GattLocalService();
  };
  

  cls.prototype.startAdvertising = function startAdvertising() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.startAdvertising = function startAdvertising(parameters) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="parameters" type="GattServiceProviderAdvertisingParameters">A param.</param>
    /// </signature>
  }


  cls.prototype.stopAdvertising = function stopAdvertising() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.createAsync = function createAsync(serviceUuid, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="serviceUuid" type="String">A param.</param>
    /// </signature>
  }



    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.GattServiceProvider = GattServiceProvider;

GattServiceProviderAdvertisementStatusChangedEventArgs = (function () {
  var cls = function GattServiceProviderAdvertisementStatusChangedEventArgs() {
    this.error = new Number();
    this.status = new GattServiceProviderAdvertisementStatus();
  };
  

  return cls;
}) ();
exports.GattServiceProviderAdvertisementStatusChangedEventArgs = GattServiceProviderAdvertisementStatusChangedEventArgs;

GattLocalCharacteristicResult = (function () {
  var cls = function GattLocalCharacteristicResult() {
    this.characteristic = new GattLocalCharacteristic();
    this.error = new Number();
  };
  

  return cls;
}) ();
exports.GattLocalCharacteristicResult = GattLocalCharacteristicResult;

GattLocalCharacteristic = (function () {
  var cls = function GattLocalCharacteristic() {
    this.characteristicProperties = new GattCharacteristicProperties();
    this.descriptors = new Object();
    this.presentationFormats = new Object();
    this.readProtectionLevel = new GattProtectionLevel();
    this.staticValue = new Object();
    this.subscribedClients = new Object();
    this.userDescription = new String();
    this.uuid = new String();
    this.writeProtectionLevel = new GattProtectionLevel();
  };
  

  cls.prototype.createDescriptorAsync = function createDescriptorAsync(descriptorUuid, parameters, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="descriptorUuid" type="String">A param.</param>
    /// <param name="parameters" type="GattLocalDescriptorParameters">A param.</param>
    /// </signature>
  }


  cls.prototype.notifyValueAsync = function notifyValueAsync(value, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// </signature>
  }

cls.prototype.notifyValueAsync = function notifyValueAsync(value, subscribedClient, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// <param name="subscribedClient" type="GattSubscribedClient">A param.</param>
    /// </signature>
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.GattLocalCharacteristic = GattLocalCharacteristic;

GattLocalDescriptorResult = (function () {
  var cls = function GattLocalDescriptorResult() {
    this.descriptor = new GattLocalDescriptor();
    this.error = new Number();
  };
  

  return cls;
}) ();
exports.GattLocalDescriptorResult = GattLocalDescriptorResult;

GattLocalDescriptor = (function () {
  var cls = function GattLocalDescriptor() {
    this.readProtectionLevel = new GattProtectionLevel();
    this.staticValue = new Object();
    this.uuid = new String();
    this.writeProtectionLevel = new GattProtectionLevel();
  };
  

    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.GattLocalDescriptor = GattLocalDescriptor;

GattSubscribedClient = (function () {
  var cls = function GattSubscribedClient() {
    this.maxNotificationSize = new Number();
    this.session = new GattSession();
  };
  

    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.GattSubscribedClient = GattSubscribedClient;

GattReadRequestedEventArgs = (function () {
  var cls = function GattReadRequestedEventArgs() {
    this.session = new GattSession();
  };
  

  cls.prototype.getRequestAsync = function getRequestAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
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
exports.GattReadRequestedEventArgs = GattReadRequestedEventArgs;

GattWriteRequestedEventArgs = (function () {
  var cls = function GattWriteRequestedEventArgs() {
    this.session = new GattSession();
  };
  

  cls.prototype.getRequestAsync = function getRequestAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
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
exports.GattWriteRequestedEventArgs = GattWriteRequestedEventArgs;

GattClientNotificationResult = (function () {
  var cls = function GattClientNotificationResult() {
    this.protocolError = new Number();
    this.status = new GattCommunicationStatus();
    this.subscribedClient = new GattSubscribedClient();
  };
  

  return cls;
}) ();
exports.GattClientNotificationResult = GattClientNotificationResult;

GattReadRequest = (function () {
  var cls = function GattReadRequest() {
    this.length = new Number();
    this.offset = new Number();
    this.state = new GattRequestState();
  };
  

  cls.prototype.respondWithValue = function respondWithValue(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.respondWithProtocolError = function respondWithProtocolError(protocolError) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="protocolError" type="Number">A param.</param>
    /// </signature>
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.GattReadRequest = GattReadRequest;

GattRequestStateChangedEventArgs = (function () {
  var cls = function GattRequestStateChangedEventArgs() {
    this.error = new Number();
    this.state = new GattRequestState();
  };
  

  return cls;
}) ();
exports.GattRequestStateChangedEventArgs = GattRequestStateChangedEventArgs;

GattWriteRequest = (function () {
  var cls = function GattWriteRequest() {
    this.offset = new Number();
    this.option = new GattWriteOption();
    this.state = new GattRequestState();
    this.value = new Object();
  };
  

  cls.prototype.respond = function respond() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.respondWithProtocolError = function respondWithProtocolError(protocolError) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="protocolError" type="Number">A param.</param>
    /// </signature>
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.GattWriteRequest = GattWriteRequest;

