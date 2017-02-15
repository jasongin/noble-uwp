declare module "windows.devices.bluetooth" {
  export enum BluetoothCacheMode {
    cached,
    uncached,
  }

  export enum BluetoothMajorClass {
    miscellaneous,
    computer,
    phone,
    networkAccessPoint,
    audioVideo,
    peripheral,
    imaging,
    wearable,
    toy,
    health,
  }

  export enum BluetoothMinorClass {
    uncategorized,
    computerDesktop,
    computerServer,
    computerLaptop,
    computerHandheld,
    computerPalmSize,
    computerWearable,
    computerTablet,
    phoneCellular,
    phoneCordless,
    phoneSmartPhone,
    phoneWired,
    phoneIsdn,
    networkFullyAvailable,
    networkUsed01To17Percent,
    networkUsed17To33Percent,
    networkUsed33To50Percent,
    networkUsed50To67Percent,
    networkUsed67To83Percent,
    networkUsed83To99Percent,
    networkNoServiceAvailable,
    audioVideoWearableHeadset,
    audioVideoHandsFree,
    audioVideoMicrophone,
    audioVideoLoudspeaker,
    audioVideoHeadphones,
    audioVideoPortableAudio,
    audioVideoCarAudio,
    audioVideoSetTopBox,
    audioVideoHifiAudioDevice,
    audioVideoVcr,
    audioVideoVideoCamera,
    audioVideoCamcorder,
    audioVideoVideoMonitor,
    audioVideoVideoDisplayAndLoudspeaker,
    audioVideoVideoConferencing,
    audioVideoGamingOrToy,
    peripheralJoystick,
    peripheralGamepad,
    peripheralRemoteControl,
    peripheralSensing,
    peripheralDigitizerTablet,
    peripheralCardReader,
    peripheralDigitalPen,
    peripheralHandheldScanner,
    peripheralHandheldGesture,
    wearableWristwatch,
    wearablePager,
    wearableJacket,
    wearableHelmet,
    wearableGlasses,
    toyRobot,
    toyVehicle,
    toyDoll,
    toyController,
    toyGame,
    healthBloodPressureMonitor,
    healthThermometer,
    healthWeighingScale,
    healthGlucoseMeter,
    healthPulseOximeter,
    healthHeartRateMonitor,
    healthHealthDataDisplay,
    healthStepCounter,
    healthBodyCompositionAnalyzer,
    healthPeakFlowMonitor,
    healthMedicationMonitor,
    healthKneeProsthesis,
    healthAnkleProsthesis,
    healthGenericHealthManager,
    healthPersonalMobilityDevice,
  }

  export enum BluetoothServiceCapabilities {
    none,
    limitedDiscoverableMode,
    positioningService,
    networkingService,
    renderingService,
    capturingService,
    objectTransferService,
    audioService,
    telephoneService,
    informationService,
  }

  export enum BluetoothConnectionStatus {
    disconnected,
    connected,
  }

  export enum BluetoothError {
    success,
    radioNotAvailable,
    resourceInUse,
    deviceNotConnected,
    otherError,
    disabledByPolicy,
    notSupported,
    disabledByUser,
    consentRequired,
    transportNotSupported,
  }

  export enum BluetoothAddressType {
    public,
    random,
    unspecified,
  }

  export class BluetoothAdapter {
    bluetoothAddress: Number;
    deviceId: String;
    isAdvertisementOffloadSupported: Boolean;
    isCentralRoleSupported: Boolean;
    isClassicSupported: Boolean;
    isLowEnergySupported: Boolean;
    isPeripheralRoleSupported: Boolean;
    constructor();

    static fromIdAsync(deviceId: String, callback: (error: Error, result: BluetoothAdapter) => void): void ;


    static getDefaultAsync(callback: (error: Error, result: BluetoothAdapter) => void): void ;


    static getDeviceSelector(): String;


    getRadioAsync(callback: (error: Error, result: Object) => void): void ;

  }

  export class BluetoothDeviceId {
    id: String;
    isClassicDevice: Boolean;
    isLowEnergyDevice: Boolean;
    constructor();

  }

  export class BluetoothUuidHelper {
    constructor();

    static fromShortId(shortId: Number): String;


    static tryGetShortId(uuid: String): Number;


  }

  export class BluetoothDevice {
    bluetoothAddress: Number;
    classOfDevice: BluetoothClassOfDevice;
    connectionStatus: BluetoothConnectionStatus;
    deviceId: String;
    hostName: Object;
    name: String;
    rfcommServices: Object;
    sdpRecords: Object;
    deviceInformation: Object;
    deviceAccessInformation: Object;
    constructor();

    static fromIdAsync(deviceId: String, callback: (error: Error, result: BluetoothDevice) => void): void ;


    static fromHostNameAsync(hostName: Object, callback: (error: Error, result: BluetoothDevice) => void): void ;


    static fromBluetoothAddressAsync(address: Number, callback: (error: Error, result: BluetoothDevice) => void): void ;


    static getDeviceSelectorFromPairingState(pairingState: Boolean): String;


    static getDeviceSelectorFromConnectionStatus(connectionStatus: BluetoothConnectionStatus): String;


    static getDeviceSelectorFromDeviceName(deviceName: String): String;


    static getDeviceSelectorFromBluetoothAddress(bluetoothAddress: Number): String;


    static getDeviceSelectorFromClassOfDevice(classOfDevice: BluetoothClassOfDevice): String;


    static getDeviceSelector(): String;


    requestAccessAsync(callback: (error: Error, result: Number) => void): void ;

    getRfcommServicesAsync(callback: (error: Error, result: Object) => void): void ;
    getRfcommServicesAsync(cacheMode: BluetoothCacheMode, callback: (error: Error, result: Object) => void): void ;

    getRfcommServicesForIdAsync(serviceId: Object, callback: (error: Error, result: Object) => void): void ;
    getRfcommServicesForIdAsync(serviceId: Object, cacheMode: BluetoothCacheMode, callback: (error: Error, result: Object) => void): void ;

    close(): void;
    addListener(type: "ConnectionStatusChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "ConnectionStatusChanged", listener: (ev: Event) => void): void ;
    on(type: "ConnectionStatusChanged", listener: (ev: Event) => void): void ;
    off(type: "ConnectionStatusChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: "NameChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "NameChanged", listener: (ev: Event) => void): void ;
    on(type: "NameChanged", listener: (ev: Event) => void): void ;
    off(type: "NameChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: "SdpRecordsChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "SdpRecordsChanged", listener: (ev: Event) => void): void ;
    on(type: "SdpRecordsChanged", listener: (ev: Event) => void): void ;
    off(type: "SdpRecordsChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: string, listener: (ev: Event) => void): void ;
    removeListener(type: string, listener: (ev: Event) => void): void ;
    on(type: string, listener: (ev: Event) => void): void ;
    off(type: string, listener: (ev: Event) => void): void ;
    

  }

  export class BluetoothClassOfDevice {
    majorClass: BluetoothMajorClass;
    minorClass: BluetoothMinorClass;
    rawValue: Number;
    serviceCapabilities: BluetoothServiceCapabilities;
    constructor();

    static fromRawValue(rawValue: Number): BluetoothClassOfDevice;


    static fromParts(majorClass: BluetoothMajorClass, minorClass: BluetoothMinorClass, serviceCapabilities: BluetoothServiceCapabilities): BluetoothClassOfDevice;


  }

  export class BluetoothLEAppearanceCategories {
    static barcodeScanner: Number;
    static bloodPressure: Number;
    static clock: Number;
    static computer: Number;
    static cycling: Number;
    static display: Number;
    static eyeGlasses: Number;
    static glucoseMeter: Number;
    static heartRate: Number;
    static humanInterfaceDevice: Number;
    static keyring: Number;
    static mediaPlayer: Number;
    static outdoorSportActivity: Number;
    static phone: Number;
    static pulseOximeter: Number;
    static remoteControl: Number;
    static runningWalking: Number;
    static tag: Number;
    static thermometer: Number;
    static uncategorized: Number;
    static watch: Number;
    static weightScale: Number;
    constructor();

  }

  export class BluetoothLEAppearanceSubcategories {
    static barcodeScanner: Number;
    static bloodPressureArm: Number;
    static bloodPressureWrist: Number;
    static cardReader: Number;
    static cyclingCadenceSensor: Number;
    static cyclingComputer: Number;
    static cyclingPowerSensor: Number;
    static cyclingSpeedCadenceSensor: Number;
    static cyclingSpeedSensor: Number;
    static digitalPen: Number;
    static digitizerTablet: Number;
    static gamepad: Number;
    static generic: Number;
    static heartRateBelt: Number;
    static joystick: Number;
    static keyboard: Number;
    static locationDisplay: Number;
    static locationNavigationDisplay: Number;
    static locationNavigationPod: Number;
    static locationPod: Number;
    static mouse: Number;
    static oximeterFingertip: Number;
    static oximeterWristWorn: Number;
    static runningWalkingInShoe: Number;
    static runningWalkingOnHip: Number;
    static runningWalkingOnShoe: Number;
    static sportsWatch: Number;
    static thermometerEar: Number;
    constructor();

  }

  export class BluetoothLEAppearance {
    category: Number;
    rawValue: Number;
    subCategory: Number;
    constructor();

    static fromRawValue(rawValue: Number): BluetoothLEAppearance;


    static fromParts(appearanceCategory: Number, appearanceSubCategory: Number): BluetoothLEAppearance;


  }

  export class BluetoothLEDevice {
    bluetoothAddress: Number;
    connectionStatus: BluetoothConnectionStatus;
    deviceId: String;
    gattServices: Object;
    name: String;
    appearance: BluetoothLEAppearance;
    bluetoothAddressType: BluetoothAddressType;
    deviceInformation: Object;
    deviceAccessInformation: Object;
    constructor();

    static fromBluetoothAddressAsync(bluetoothAddress: Number, bluetoothAddressType: BluetoothAddressType, callback: (error: Error, result: BluetoothLEDevice) => void): void ;
    static fromBluetoothAddressAsync(bluetoothAddress: Number, callback: (error: Error, result: BluetoothLEDevice) => void): void ;


    static fromIdAsync(deviceId: String, callback: (error: Error, result: BluetoothLEDevice) => void): void ;


    static getDeviceSelectorFromPairingState(pairingState: Boolean): String;


    static getDeviceSelectorFromConnectionStatus(connectionStatus: BluetoothConnectionStatus): String;


    static getDeviceSelectorFromDeviceName(deviceName: String): String;


    static getDeviceSelectorFromBluetoothAddress(bluetoothAddress: Number): String;
    static getDeviceSelectorFromBluetoothAddress(bluetoothAddress: Number, bluetoothAddressType: BluetoothAddressType): String;


    static getDeviceSelectorFromAppearance(appearance: BluetoothLEAppearance): String;


    static getDeviceSelector(): String;


    requestAccessAsync(callback: (error: Error, result: Number) => void): void ;

    getGattServicesAsync(callback: (error: Error, result: Object) => void): void ;
    getGattServicesAsync(cacheMode: BluetoothCacheMode, callback: (error: Error, result: Object) => void): void ;

    getGattServicesForUuidAsync(serviceUuid: String, callback: (error: Error, result: Object) => void): void ;
    getGattServicesForUuidAsync(serviceUuid: String, cacheMode: BluetoothCacheMode, callback: (error: Error, result: Object) => void): void ;

    getGattService(serviceUuid: String): Object;

    close(): void;
    addListener(type: "ConnectionStatusChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "ConnectionStatusChanged", listener: (ev: Event) => void): void ;
    on(type: "ConnectionStatusChanged", listener: (ev: Event) => void): void ;
    off(type: "ConnectionStatusChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: "GattServicesChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "GattServicesChanged", listener: (ev: Event) => void): void ;
    on(type: "GattServicesChanged", listener: (ev: Event) => void): void ;
    off(type: "GattServicesChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: "NameChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "NameChanged", listener: (ev: Event) => void): void ;
    on(type: "NameChanged", listener: (ev: Event) => void): void ;
    off(type: "NameChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: string, listener: (ev: Event) => void): void ;
    removeListener(type: string, listener: (ev: Event) => void): void ;
    on(type: string, listener: (ev: Event) => void): void ;
    off(type: string, listener: (ev: Event) => void): void ;
    

  }

  export class BluetoothSignalStrengthFilter {
    samplingInterval: Number;
    outOfRangeTimeout: Number;
    outOfRangeThresholdInDBm: Number;
    inRangeThresholdInDBm: Number;
    constructor();

  }

}



