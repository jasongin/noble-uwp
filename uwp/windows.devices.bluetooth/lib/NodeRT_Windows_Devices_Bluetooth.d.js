_BluetoothCacheMode = function () {
  this.cached = 0;
  this.uncached = 1;
}
exports.BluetoothCacheMode = new _BluetoothCacheMode();

_BluetoothMajorClass = function () {
  this.miscellaneous = 0;
  this.computer = 1;
  this.phone = 2;
  this.networkAccessPoint = 3;
  this.audioVideo = 4;
  this.peripheral = 5;
  this.imaging = 6;
  this.wearable = 7;
  this.toy = 8;
  this.health = 9;
}
exports.BluetoothMajorClass = new _BluetoothMajorClass();

_BluetoothMinorClass = function () {
  this.uncategorized = 0;
  this.computerDesktop = 1;
  this.computerServer = 2;
  this.computerLaptop = 3;
  this.computerHandheld = 4;
  this.computerPalmSize = 5;
  this.computerWearable = 6;
  this.computerTablet = 7;
  this.phoneCellular = 8;
  this.phoneCordless = 9;
  this.phoneSmartPhone = 10;
  this.phoneWired = 11;
  this.phoneIsdn = 12;
  this.networkFullyAvailable = 13;
  this.networkUsed01To17Percent = 14;
  this.networkUsed17To33Percent = 15;
  this.networkUsed33To50Percent = 16;
  this.networkUsed50To67Percent = 17;
  this.networkUsed67To83Percent = 18;
  this.networkUsed83To99Percent = 19;
  this.networkNoServiceAvailable = 20;
  this.audioVideoWearableHeadset = 21;
  this.audioVideoHandsFree = 22;
  this.audioVideoMicrophone = 23;
  this.audioVideoLoudspeaker = 24;
  this.audioVideoHeadphones = 25;
  this.audioVideoPortableAudio = 26;
  this.audioVideoCarAudio = 27;
  this.audioVideoSetTopBox = 28;
  this.audioVideoHifiAudioDevice = 29;
  this.audioVideoVcr = 30;
  this.audioVideoVideoCamera = 31;
  this.audioVideoCamcorder = 32;
  this.audioVideoVideoMonitor = 33;
  this.audioVideoVideoDisplayAndLoudspeaker = 34;
  this.audioVideoVideoConferencing = 35;
  this.audioVideoGamingOrToy = 36;
  this.peripheralJoystick = 37;
  this.peripheralGamepad = 38;
  this.peripheralRemoteControl = 39;
  this.peripheralSensing = 40;
  this.peripheralDigitizerTablet = 41;
  this.peripheralCardReader = 42;
  this.peripheralDigitalPen = 43;
  this.peripheralHandheldScanner = 44;
  this.peripheralHandheldGesture = 45;
  this.wearableWristwatch = 46;
  this.wearablePager = 47;
  this.wearableJacket = 48;
  this.wearableHelmet = 49;
  this.wearableGlasses = 50;
  this.toyRobot = 51;
  this.toyVehicle = 52;
  this.toyDoll = 53;
  this.toyController = 54;
  this.toyGame = 55;
  this.healthBloodPressureMonitor = 56;
  this.healthThermometer = 57;
  this.healthWeighingScale = 58;
  this.healthGlucoseMeter = 59;
  this.healthPulseOximeter = 60;
  this.healthHeartRateMonitor = 61;
  this.healthHealthDataDisplay = 62;
  this.healthStepCounter = 63;
  this.healthBodyCompositionAnalyzer = 64;
  this.healthPeakFlowMonitor = 65;
  this.healthMedicationMonitor = 66;
  this.healthKneeProsthesis = 67;
  this.healthAnkleProsthesis = 68;
  this.healthGenericHealthManager = 69;
  this.healthPersonalMobilityDevice = 70;
}
exports.BluetoothMinorClass = new _BluetoothMinorClass();

_BluetoothServiceCapabilities = function () {
  this.none = 0;
  this.limitedDiscoverableMode = 1;
  this.positioningService = 2;
  this.networkingService = 3;
  this.renderingService = 4;
  this.capturingService = 5;
  this.objectTransferService = 6;
  this.audioService = 7;
  this.telephoneService = 8;
  this.informationService = 9;
}
exports.BluetoothServiceCapabilities = new _BluetoothServiceCapabilities();

_BluetoothConnectionStatus = function () {
  this.disconnected = 0;
  this.connected = 1;
}
exports.BluetoothConnectionStatus = new _BluetoothConnectionStatus();

_BluetoothError = function () {
  this.success = 0;
  this.radioNotAvailable = 1;
  this.resourceInUse = 2;
  this.deviceNotConnected = 3;
  this.otherError = 4;
  this.disabledByPolicy = 5;
  this.notSupported = 6;
  this.disabledByUser = 7;
  this.consentRequired = 8;
  this.transportNotSupported = 9;
}
exports.BluetoothError = new _BluetoothError();

_BluetoothAddressType = function () {
  this.public = 0;
  this.random = 1;
  this.unspecified = 2;
}
exports.BluetoothAddressType = new _BluetoothAddressType();

BluetoothAdapter = (function () {
  var cls = function BluetoothAdapter() {
    this.bluetoothAddress = new Number();
    this.deviceId = new String();
    this.isAdvertisementOffloadSupported = new Boolean();
    this.isCentralRoleSupported = new Boolean();
    this.isClassicSupported = new Boolean();
    this.isLowEnergySupported = new Boolean();
    this.isPeripheralRoleSupported = new Boolean();
  };
  

  cls.prototype.getRadioAsync = function getRadioAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.fromIdAsync = function fromIdAsync(deviceId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="deviceId" type="String">A param.</param>
    /// </signature>
  }



  cls.getDefaultAsync = function getDefaultAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }



  cls.getDeviceSelector = function getDeviceSelector() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  return cls;
}) ();
exports.BluetoothAdapter = BluetoothAdapter;

BluetoothDeviceId = (function () {
  var cls = function BluetoothDeviceId() {
    this.id = new String();
    this.isClassicDevice = new Boolean();
    this.isLowEnergyDevice = new Boolean();
  };
  

  return cls;
}) ();
exports.BluetoothDeviceId = BluetoothDeviceId;

BluetoothUuidHelper = (function () {
  var cls = function BluetoothUuidHelper() {
  };
  

  cls.fromShortId = function fromShortId(shortId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="shortId" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.tryGetShortId = function tryGetShortId(uuid) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="uuid" type="String">A param.</param>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  return cls;
}) ();
exports.BluetoothUuidHelper = BluetoothUuidHelper;

BluetoothDevice = (function () {
  var cls = function BluetoothDevice() {
    this.bluetoothAddress = new Number();
    this.classOfDevice = new BluetoothClassOfDevice();
    this.connectionStatus = new BluetoothConnectionStatus();
    this.deviceId = new String();
    this.hostName = new Object();
    this.name = new String();
    this.rfcommServices = new Object();
    this.sdpRecords = new Object();
    this.deviceInformation = new Object();
    this.deviceAccessInformation = new Object();
  };
  

  cls.prototype.requestAccessAsync = function requestAccessAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.getRfcommServicesAsync = function getRfcommServicesAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.getRfcommServicesAsync = function getRfcommServicesAsync(cacheMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="cacheMode" type="BluetoothCacheMode">A param.</param>
    /// </signature>
  }


  cls.prototype.getRfcommServicesForIdAsync = function getRfcommServicesForIdAsync(serviceId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="serviceId" type="Object">A param.</param>
    /// </signature>
  }

cls.prototype.getRfcommServicesForIdAsync = function getRfcommServicesForIdAsync(serviceId, cacheMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="serviceId" type="Object">A param.</param>
    /// <param name="cacheMode" type="BluetoothCacheMode">A param.</param>
    /// </signature>
  }


  cls.prototype.close = function close() {
}


  cls.fromIdAsync = function fromIdAsync(deviceId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="deviceId" type="String">A param.</param>
    /// </signature>
  }



  cls.fromHostNameAsync = function fromHostNameAsync(hostName, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="hostName" type="Object">A param.</param>
    /// </signature>
  }



  cls.fromBluetoothAddressAsync = function fromBluetoothAddressAsync(address, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="address" type="Number">A param.</param>
    /// </signature>
  }



  cls.getDeviceSelectorFromPairingState = function getDeviceSelectorFromPairingState(pairingState) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="pairingState" type="Boolean">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.getDeviceSelectorFromConnectionStatus = function getDeviceSelectorFromConnectionStatus(connectionStatus) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="connectionStatus" type="BluetoothConnectionStatus">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.getDeviceSelectorFromDeviceName = function getDeviceSelectorFromDeviceName(deviceName) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="deviceName" type="String">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.getDeviceSelectorFromBluetoothAddress = function getDeviceSelectorFromBluetoothAddress(bluetoothAddress) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="bluetoothAddress" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.getDeviceSelectorFromClassOfDevice = function getDeviceSelectorFromClassOfDevice(classOfDevice) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="classOfDevice" type="BluetoothClassOfDevice">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.getDeviceSelector = function getDeviceSelector() {
    /// <signature>
    /// <summary>Function summary.</summary>
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
exports.BluetoothDevice = BluetoothDevice;

BluetoothClassOfDevice = (function () {
  var cls = function BluetoothClassOfDevice() {
    this.majorClass = new BluetoothMajorClass();
    this.minorClass = new BluetoothMinorClass();
    this.rawValue = new Number();
    this.serviceCapabilities = new BluetoothServiceCapabilities();
  };
  

  cls.fromRawValue = function fromRawValue(rawValue) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="rawValue" type="Number">A param.</param>
    /// <returns type="BluetoothClassOfDevice" />
    /// </signature>
    return new BluetoothClassOfDevice();
  }


  cls.fromParts = function fromParts(majorClass, minorClass, serviceCapabilities) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="majorClass" type="BluetoothMajorClass">A param.</param>
    /// <param name="minorClass" type="BluetoothMinorClass">A param.</param>
    /// <param name="serviceCapabilities" type="BluetoothServiceCapabilities">A param.</param>
    /// <returns type="BluetoothClassOfDevice" />
    /// </signature>
    return new BluetoothClassOfDevice();
  }


  return cls;
}) ();
exports.BluetoothClassOfDevice = BluetoothClassOfDevice;

BluetoothLEAppearanceCategories = (function () {
  var cls = function BluetoothLEAppearanceCategories() {
  };
  

  cls.barcodeScanner = new Number();
  cls.bloodPressure = new Number();
  cls.clock = new Number();
  cls.computer = new Number();
  cls.cycling = new Number();
  cls.display = new Number();
  cls.eyeGlasses = new Number();
  cls.glucoseMeter = new Number();
  cls.heartRate = new Number();
  cls.humanInterfaceDevice = new Number();
  cls.keyring = new Number();
  cls.mediaPlayer = new Number();
  cls.outdoorSportActivity = new Number();
  cls.phone = new Number();
  cls.pulseOximeter = new Number();
  cls.remoteControl = new Number();
  cls.runningWalking = new Number();
  cls.tag = new Number();
  cls.thermometer = new Number();
  cls.uncategorized = new Number();
  cls.watch = new Number();
  cls.weightScale = new Number();
  return cls;
}) ();
exports.BluetoothLEAppearanceCategories = BluetoothLEAppearanceCategories;

BluetoothLEAppearanceSubcategories = (function () {
  var cls = function BluetoothLEAppearanceSubcategories() {
  };
  

  cls.barcodeScanner = new Number();
  cls.bloodPressureArm = new Number();
  cls.bloodPressureWrist = new Number();
  cls.cardReader = new Number();
  cls.cyclingCadenceSensor = new Number();
  cls.cyclingComputer = new Number();
  cls.cyclingPowerSensor = new Number();
  cls.cyclingSpeedCadenceSensor = new Number();
  cls.cyclingSpeedSensor = new Number();
  cls.digitalPen = new Number();
  cls.digitizerTablet = new Number();
  cls.gamepad = new Number();
  cls.generic = new Number();
  cls.heartRateBelt = new Number();
  cls.joystick = new Number();
  cls.keyboard = new Number();
  cls.locationDisplay = new Number();
  cls.locationNavigationDisplay = new Number();
  cls.locationNavigationPod = new Number();
  cls.locationPod = new Number();
  cls.mouse = new Number();
  cls.oximeterFingertip = new Number();
  cls.oximeterWristWorn = new Number();
  cls.runningWalkingInShoe = new Number();
  cls.runningWalkingOnHip = new Number();
  cls.runningWalkingOnShoe = new Number();
  cls.sportsWatch = new Number();
  cls.thermometerEar = new Number();
  return cls;
}) ();
exports.BluetoothLEAppearanceSubcategories = BluetoothLEAppearanceSubcategories;

BluetoothLEAppearance = (function () {
  var cls = function BluetoothLEAppearance() {
    this.category = new Number();
    this.rawValue = new Number();
    this.subCategory = new Number();
  };
  

  cls.fromRawValue = function fromRawValue(rawValue) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="rawValue" type="Number">A param.</param>
    /// <returns type="BluetoothLEAppearance" />
    /// </signature>
    return new BluetoothLEAppearance();
  }


  cls.fromParts = function fromParts(appearanceCategory, appearanceSubCategory) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="appearanceCategory" type="Number">A param.</param>
    /// <param name="appearanceSubCategory" type="Number">A param.</param>
    /// <returns type="BluetoothLEAppearance" />
    /// </signature>
    return new BluetoothLEAppearance();
  }


  return cls;
}) ();
exports.BluetoothLEAppearance = BluetoothLEAppearance;

BluetoothLEDevice = (function () {
  var cls = function BluetoothLEDevice() {
    this.bluetoothAddress = new Number();
    this.connectionStatus = new BluetoothConnectionStatus();
    this.deviceId = new String();
    this.gattServices = new Object();
    this.name = new String();
    this.appearance = new BluetoothLEAppearance();
    this.bluetoothAddressType = new BluetoothAddressType();
    this.deviceInformation = new Object();
    this.deviceAccessInformation = new Object();
  };
  

  cls.prototype.requestAccessAsync = function requestAccessAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.getGattServicesAsync = function getGattServicesAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.getGattServicesAsync = function getGattServicesAsync(cacheMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="cacheMode" type="BluetoothCacheMode">A param.</param>
    /// </signature>
  }


  cls.prototype.getGattServicesForUuidAsync = function getGattServicesForUuidAsync(serviceUuid, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="serviceUuid" type="String">A param.</param>
    /// </signature>
  }

cls.prototype.getGattServicesForUuidAsync = function getGattServicesForUuidAsync(serviceUuid, cacheMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="serviceUuid" type="String">A param.</param>
    /// <param name="cacheMode" type="BluetoothCacheMode">A param.</param>
    /// </signature>
  }


  cls.prototype.getGattService = function getGattService(serviceUuid) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="serviceUuid" type="String">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.close = function close() {
}


  cls.fromBluetoothAddressAsync = function fromBluetoothAddressAsync(bluetoothAddress, bluetoothAddressType, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="bluetoothAddress" type="Number">A param.</param>
    /// <param name="bluetoothAddressType" type="BluetoothAddressType">A param.</param>
    /// </signature>
  }

cls.fromBluetoothAddressAsync = function fromBluetoothAddressAsync(bluetoothAddress, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="bluetoothAddress" type="Number">A param.</param>
    /// </signature>
  }



  cls.fromIdAsync = function fromIdAsync(deviceId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="deviceId" type="String">A param.</param>
    /// </signature>
  }



  cls.getDeviceSelectorFromPairingState = function getDeviceSelectorFromPairingState(pairingState) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="pairingState" type="Boolean">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.getDeviceSelectorFromConnectionStatus = function getDeviceSelectorFromConnectionStatus(connectionStatus) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="connectionStatus" type="BluetoothConnectionStatus">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.getDeviceSelectorFromDeviceName = function getDeviceSelectorFromDeviceName(deviceName) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="deviceName" type="String">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.getDeviceSelectorFromBluetoothAddress = function getDeviceSelectorFromBluetoothAddress(bluetoothAddress) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="bluetoothAddress" type="Number">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }

cls.getDeviceSelectorFromBluetoothAddress = function getDeviceSelectorFromBluetoothAddress(bluetoothAddress, bluetoothAddressType) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="bluetoothAddress" type="Number">A param.</param>
    /// <param name="bluetoothAddressType" type="BluetoothAddressType">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.getDeviceSelectorFromAppearance = function getDeviceSelectorFromAppearance(appearance) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="appearance" type="BluetoothLEAppearance">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.getDeviceSelector = function getDeviceSelector() {
    /// <signature>
    /// <summary>Function summary.</summary>
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
exports.BluetoothLEDevice = BluetoothLEDevice;

BluetoothSignalStrengthFilter = (function () {
  var cls = function BluetoothSignalStrengthFilter() {
    this.samplingInterval = new Number();
    this.outOfRangeTimeout = new Number();
    this.outOfRangeThresholdInDBm = new Number();
    this.inRangeThresholdInDBm = new Number();
  };
  

  return cls;
}) ();
exports.BluetoothSignalStrengthFilter = BluetoothSignalStrengthFilter;

