declare module "windows.devices.bluetooth.genericattributeprofile" {
  export enum GattSessionStatus {
    closed,
    active,
  }

  export enum GattCharacteristicProperties {
    none,
    broadcast,
    read,
    writeWithoutResponse,
    write,
    notify,
    indicate,
    authenticatedSignedWrites,
    extendedProperties,
    reliableWrites,
    writableAuxiliaries,
  }

  export enum GattClientCharacteristicConfigurationDescriptorValue {
    none,
    notify,
    indicate,
  }

  export enum GattProtectionLevel {
    plain,
    authenticationRequired,
    encryptionRequired,
    encryptionAndAuthenticationRequired,
  }

  export enum GattWriteOption {
    writeWithResponse,
    writeWithoutResponse,
  }

  export enum GattCommunicationStatus {
    success,
    unreachable,
    protocolError,
    accessDenied,
  }

  export enum GattSharingMode {
    unspecified,
    exclusive,
    sharedReadOnly,
    sharedReadAndWrite,
  }

  export enum GattOpenStatus {
    unspecified,
    success,
    alreadyOpened,
    notFound,
    sharingViolation,
    accessDenied,
  }

  export enum GattRequestState {
    pending,
    completed,
    canceled,
  }

  export enum GattServiceProviderAdvertisementStatus {
    created,
    stopped,
    started,
    aborted,
  }

  export class GattDeviceService {
    attributeHandle: Number;
    deviceId: String;
    uuid: String;
    device: Object;
    parentServices: Object;
    deviceAccessInformation: Object;
    session: GattSession;
    sharingMode: GattSharingMode;
    constructor();

    static fromIdAsync(deviceId: String, sharingMode: GattSharingMode, callback: (error: Error, result: GattDeviceService) => void): void ;
    static fromIdAsync(deviceId: String, callback: (error: Error, result: GattDeviceService) => void): void ;


    static getDeviceSelectorForBluetoothDeviceId(bluetoothDeviceId: Object): String;
    static getDeviceSelectorForBluetoothDeviceId(bluetoothDeviceId: Object, cacheMode: Number): String;


    static getDeviceSelectorForBluetoothDeviceIdAndUuid(bluetoothDeviceId: Object, serviceUuid: String): String;
    static getDeviceSelectorForBluetoothDeviceIdAndUuid(bluetoothDeviceId: Object, serviceUuid: String, cacheMode: Number): String;


    static getDeviceSelectorFromUuid(serviceUuid: String): String;


    static getDeviceSelectorFromShortId(serviceShortId: Number): String;


    static convertShortIdToUuid(shortId: Number): String;


    requestAccessAsync(callback: (error: Error, result: Number) => void): void ;

    openAsync(sharingMode: GattSharingMode, callback: (error: Error, result: GattOpenStatus) => void): void ;

    getCharacteristicsAsync(callback: (error: Error, result: GattCharacteristicsResult) => void): void ;
    getCharacteristicsAsync(cacheMode: Number, callback: (error: Error, result: GattCharacteristicsResult) => void): void ;

    getCharacteristicsForUuidAsync(characteristicUuid: String, callback: (error: Error, result: GattCharacteristicsResult) => void): void ;
    getCharacteristicsForUuidAsync(characteristicUuid: String, cacheMode: Number, callback: (error: Error, result: GattCharacteristicsResult) => void): void ;

    getIncludedServicesAsync(callback: (error: Error, result: GattDeviceServicesResult) => void): void ;
    getIncludedServicesAsync(cacheMode: Number, callback: (error: Error, result: GattDeviceServicesResult) => void): void ;

    getIncludedServicesForUuidAsync(serviceUuid: String, callback: (error: Error, result: GattDeviceServicesResult) => void): void ;
    getIncludedServicesForUuidAsync(serviceUuid: String, cacheMode: Number, callback: (error: Error, result: GattDeviceServicesResult) => void): void ;

    getCharacteristics(characteristicUuid: String): Object;

    getIncludedServices(serviceUuid: String): Object;

    close(): void;
    getAllCharacteristics(): Object;

    getAllIncludedServices(): Object;

  }

  export class GattDeviceServicesResult {
    protocolError: Number;
    services: Object;
    status: GattCommunicationStatus;
    constructor();

  }

  export class GattProtocolError {
    static attributeNotFound: Number;
    static attributeNotLong: Number;
    static insufficientAuthentication: Number;
    static insufficientAuthorization: Number;
    static insufficientEncryption: Number;
    static insufficientEncryptionKeySize: Number;
    static insufficientResources: Number;
    static invalidAttributeValueLength: Number;
    static invalidHandle: Number;
    static invalidOffset: Number;
    static invalidPdu: Number;
    static prepareQueueFull: Number;
    static readNotPermitted: Number;
    static requestNotSupported: Number;
    static unlikelyError: Number;
    static unsupportedGroupType: Number;
    static writeNotPermitted: Number;
    constructor();

  }

  export class GattSession {
    maintainConnection: Boolean;
    canMaintainConnection: Boolean;
    deviceId: Object;
    maxPduSize: Number;
    sessionStatus: GattSessionStatus;
    constructor();

    static fromDeviceIdAsync(deviceId: Object, callback: (error: Error, result: GattSession) => void): void ;


    close(): void;
    addListener(type: "MaxPduSizeChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "MaxPduSizeChanged", listener: (ev: Event) => void): void ;
    on(type: "MaxPduSizeChanged", listener: (ev: Event) => void): void ;
    off(type: "MaxPduSizeChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: "SessionStatusChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "SessionStatusChanged", listener: (ev: Event) => void): void ;
    on(type: "SessionStatusChanged", listener: (ev: Event) => void): void ;
    off(type: "SessionStatusChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: string, listener: (ev: Event) => void): void ;
    removeListener(type: string, listener: (ev: Event) => void): void ;
    on(type: string, listener: (ev: Event) => void): void ;
    off(type: string, listener: (ev: Event) => void): void ;
    

  }

  export class GattSessionStatusChangedEventArgs {
    error: Number;
    status: GattSessionStatus;
    constructor();

  }

  export class GattCharacteristic {
    protectionLevel: GattProtectionLevel;
    attributeHandle: Number;
    characteristicProperties: GattCharacteristicProperties;
    presentationFormats: Object;
    userDescription: String;
    uuid: String;
    service: GattDeviceService;
    constructor();

    static convertShortIdToUuid(shortId: Number): String;


    readValueAsync(callback: (error: Error, result: GattReadResult) => void): void ;
    readValueAsync(cacheMode: Number, callback: (error: Error, result: GattReadResult) => void): void ;

    writeValueAsync(value: Object, callback: (error: Error, result: GattCommunicationStatus) => void): void ;
    writeValueAsync(value: Object, writeOption: GattWriteOption, callback: (error: Error, result: GattCommunicationStatus) => void): void ;

    readClientCharacteristicConfigurationDescriptorAsync(callback: (error: Error, result: GattReadClientCharacteristicConfigurationDescriptorResult) => void): void ;

    writeClientCharacteristicConfigurationDescriptorAsync(clientCharacteristicConfigurationDescriptorValue: GattClientCharacteristicConfigurationDescriptorValue, callback: (error: Error, result: GattCommunicationStatus) => void): void ;

    getDescriptorsAsync(callback: (error: Error, result: GattDescriptorsResult) => void): void ;
    getDescriptorsAsync(cacheMode: Number, callback: (error: Error, result: GattDescriptorsResult) => void): void ;

    getDescriptorsForUuidAsync(descriptorUuid: String, callback: (error: Error, result: GattDescriptorsResult) => void): void ;
    getDescriptorsForUuidAsync(descriptorUuid: String, cacheMode: Number, callback: (error: Error, result: GattDescriptorsResult) => void): void ;

    writeValueWithResultAsync(value: Object, callback: (error: Error, result: GattWriteResult) => void): void ;
    writeValueWithResultAsync(value: Object, writeOption: GattWriteOption, callback: (error: Error, result: GattWriteResult) => void): void ;

    writeClientCharacteristicConfigurationDescriptorWithResultAsync(clientCharacteristicConfigurationDescriptorValue: GattClientCharacteristicConfigurationDescriptorValue, callback: (error: Error, result: GattWriteResult) => void): void ;

    getDescriptors(descriptorUuid: String): Object;

    getAllDescriptors(): Object;

    addListener(type: "ValueChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "ValueChanged", listener: (ev: Event) => void): void ;
    on(type: "ValueChanged", listener: (ev: Event) => void): void ;
    off(type: "ValueChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: string, listener: (ev: Event) => void): void ;
    removeListener(type: string, listener: (ev: Event) => void): void ;
    on(type: string, listener: (ev: Event) => void): void ;
    off(type: string, listener: (ev: Event) => void): void ;
    

  }

  export class GattCharacteristicsResult {
    characteristics: Object;
    protocolError: Number;
    status: GattCommunicationStatus;
    constructor();

  }

  export class GattDescriptor {
    protectionLevel: GattProtectionLevel;
    attributeHandle: Number;
    uuid: String;
    constructor();

    static convertShortIdToUuid(shortId: Number): String;


    readValueAsync(callback: (error: Error, result: GattReadResult) => void): void ;
    readValueAsync(cacheMode: Number, callback: (error: Error, result: GattReadResult) => void): void ;

    writeValueAsync(value: Object, callback: (error: Error, result: GattCommunicationStatus) => void): void ;

    writeValueWithResultAsync(value: Object, callback: (error: Error, result: GattWriteResult) => void): void ;

  }

  export class GattPresentationFormat {
    static bluetoothSigAssignedNumbers: Number;
    description: Number;
    exponent: Number;
    formatType: Number;
    namespace: Number;
    unit: Number;
    constructor();

    static fromParts(formatType: Number, exponent: Number, unit: Number, namespaceId: Number, description: Number): GattPresentationFormat;


  }

  export class GattReadResult {
    status: GattCommunicationStatus;
    value: Object;
    protocolError: Number;
    constructor();

  }

  export class GattReadClientCharacteristicConfigurationDescriptorResult {
    clientCharacteristicConfigurationDescriptor: GattClientCharacteristicConfigurationDescriptorValue;
    status: GattCommunicationStatus;
    protocolError: Number;
    constructor();

  }

  export class GattValueChangedEventArgs {
    characteristicValue: Object;
    timestamp: Date;
    constructor();

  }

  export class GattDescriptorsResult {
    descriptors: Object;
    protocolError: Number;
    status: GattCommunicationStatus;
    constructor();

  }

  export class GattWriteResult {
    protocolError: Number;
    status: GattCommunicationStatus;
    constructor();

  }

  export class GattPresentationFormatTypes {
    static bit2: Number;
    static boolean: Number;
    static dUInt16: Number;
    static float: Number;
    static float32: Number;
    static float64: Number;
    static nibble: Number;
    static sFloat: Number;
    static sInt12: Number;
    static sInt128: Number;
    static sInt16: Number;
    static sInt24: Number;
    static sInt32: Number;
    static sInt48: Number;
    static sInt64: Number;
    static sInt8: Number;
    static struct: Number;
    static uInt12: Number;
    static uInt128: Number;
    static uInt16: Number;
    static uInt24: Number;
    static uInt32: Number;
    static uInt48: Number;
    static uInt64: Number;
    static uInt8: Number;
    static utf16: Number;
    static utf8: Number;
    constructor();

  }

  export class GattServiceUuids {
    static cyclingSpeedAndCadence: String;
    static battery: String;
    static bloodPressure: String;
    static genericAccess: String;
    static genericAttribute: String;
    static glucose: String;
    static healthThermometer: String;
    static heartRate: String;
    static runningSpeedAndCadence: String;
    static nextDstChange: String;
    static alertNotification: String;
    static currentTime: String;
    static cyclingPower: String;
    static deviceInformation: String;
    static humanInterfaceDevice: String;
    static immediateAlert: String;
    static linkLoss: String;
    static locationAndNavigation: String;
    static phoneAlertStatus: String;
    static referenceTimeUpdate: String;
    static scanParameters: String;
    static txPower: String;
    constructor();

  }

  export class GattCharacteristicUuids {
    static batteryLevel: String;
    static bloodPressureFeature: String;
    static bloodPressureMeasurement: String;
    static bodySensorLocation: String;
    static cscFeature: String;
    static cscMeasurement: String;
    static glucoseFeature: String;
    static glucoseMeasurement: String;
    static glucoseMeasurementContext: String;
    static heartRateControlPoint: String;
    static heartRateMeasurement: String;
    static intermediateCuffPressure: String;
    static intermediateTemperature: String;
    static measurementInterval: String;
    static recordAccessControlPoint: String;
    static rscFeature: String;
    static rscMeasurement: String;
    static sCControlPoint: String;
    static sensorLocation: String;
    static temperatureMeasurement: String;
    static temperatureType: String;
    static lnFeature: String;
    static alertCategoryId: String;
    static alertCategoryIdBitMask: String;
    static alertLevel: String;
    static alertNotificationControlPoint: String;
    static alertStatus: String;
    static bootKeyboardInputReport: String;
    static bootKeyboardOutputReport: String;
    static bootMouseInputReport: String;
    static currentTime: String;
    static cyclingPowerControlPoint: String;
    static cyclingPowerFeature: String;
    static cyclingPowerMeasurement: String;
    static cyclingPowerVector: String;
    static dateTime: String;
    static dayDateTime: String;
    static dayOfWeek: String;
    static dstOffset: String;
    static exactTime256: String;
    static firmwareRevisionString: String;
    static gapAppearance: String;
    static gapDeviceName: String;
    static gapPeripheralPreferredConnectionParameters: String;
    static gapPeripheralPrivacyFlag: String;
    static gapReconnectionAddress: String;
    static gattServiceChanged: String;
    static hardwareRevisionString: String;
    static hidControlPoint: String;
    static hidInformation: String;
    static ieee1107320601RegulatoryCertificationDataList: String;
    static lnControlPoint: String;
    static localTimeInformation: String;
    static locationAndSpeed: String;
    static manufacturerNameString: String;
    static modelNumberString: String;
    static navigation: String;
    static newAlert: String;
    static pnpId: String;
    static positionQuality: String;
    static protocolMode: String;
    static referenceTimeInformation: String;
    static report: String;
    static reportMap: String;
    static ringerControlPoint: String;
    static ringerSetting: String;
    static scanIntervalWindow: String;
    static scanRefresh: String;
    static serialNumberString: String;
    static softwareRevisionString: String;
    static supportUnreadAlertCategory: String;
    static supportedNewAlertCategory: String;
    static systemId: String;
    static timeAccuracy: String;
    static timeSource: String;
    static timeUpdateControlPoint: String;
    static timeUpdateState: String;
    static timeWithDst: String;
    static timeZone: String;
    static txPowerLevel: String;
    static unreadAlertStatus: String;
    constructor();

  }

  export class GattDescriptorUuids {
    static characteristicAggregateFormat: String;
    static characteristicExtendedProperties: String;
    static characteristicPresentationFormat: String;
    static characteristicUserDescription: String;
    static clientCharacteristicConfiguration: String;
    static serverCharacteristicConfiguration: String;
    constructor();

  }

  export class GattReliableWriteTransaction {
    constructor();

    commitAsync(callback: (error: Error, result: GattCommunicationStatus) => void): void ;

    commitWithResultAsync(callback: (error: Error, result: GattWriteResult) => void): void ;

    writeValue(characteristic: GattCharacteristic, value: Object): void;

  }

  export class GattServiceProviderAdvertisingParameters {
    isDiscoverable: Boolean;
    isConnectable: Boolean;
    constructor();

  }

  export class GattLocalCharacteristicParameters {
    writeProtectionLevel: GattProtectionLevel;
    userDescription: String;
    staticValue: Object;
    readProtectionLevel: GattProtectionLevel;
    characteristicProperties: GattCharacteristicProperties;
    presentationFormats: Object;
    constructor();

  }

  export class GattLocalDescriptorParameters {
    writeProtectionLevel: GattProtectionLevel;
    staticValue: Object;
    readProtectionLevel: GattProtectionLevel;
    constructor();

  }

  export class GattServiceProviderResult {
    error: Number;
    serviceProvider: GattServiceProvider;
    constructor();

  }

  export class GattLocalService {
    characteristics: Object;
    uuid: String;
    constructor();

    createCharacteristicAsync(characteristicUuid: String, parameters: GattLocalCharacteristicParameters, callback: (error: Error, result: GattLocalCharacteristicResult) => void): void ;

  }

  export class GattServiceProvider {
    advertisementStatus: GattServiceProviderAdvertisementStatus;
    service: GattLocalService;
    constructor();

    static createAsync(serviceUuid: String, callback: (error: Error, result: GattServiceProviderResult) => void): void ;


    startAdvertising(): void;
    startAdvertising(parameters: GattServiceProviderAdvertisingParameters): void;

    stopAdvertising(): void;

    addListener(type: "AdvertisementStatusChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "AdvertisementStatusChanged", listener: (ev: Event) => void): void ;
    on(type: "AdvertisementStatusChanged", listener: (ev: Event) => void): void ;
    off(type: "AdvertisementStatusChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: string, listener: (ev: Event) => void): void ;
    removeListener(type: string, listener: (ev: Event) => void): void ;
    on(type: string, listener: (ev: Event) => void): void ;
    off(type: string, listener: (ev: Event) => void): void ;
    

  }

  export class GattServiceProviderAdvertisementStatusChangedEventArgs {
    error: Number;
    status: GattServiceProviderAdvertisementStatus;
    constructor();

  }

  export class GattLocalCharacteristicResult {
    characteristic: GattLocalCharacteristic;
    error: Number;
    constructor();

  }

  export class GattLocalCharacteristic {
    characteristicProperties: GattCharacteristicProperties;
    descriptors: Object;
    presentationFormats: Object;
    readProtectionLevel: GattProtectionLevel;
    staticValue: Object;
    subscribedClients: Object;
    userDescription: String;
    uuid: String;
    writeProtectionLevel: GattProtectionLevel;
    constructor();

    createDescriptorAsync(descriptorUuid: String, parameters: GattLocalDescriptorParameters, callback: (error: Error, result: GattLocalDescriptorResult) => void): void ;

    notifyValueAsync(value: Object, callback: (error: Error, result: Object) => void): void ;
    notifyValueAsync(value: Object, subscribedClient: GattSubscribedClient, callback: (error: Error, result: GattClientNotificationResult) => void): void ;

    addListener(type: "ReadRequested", listener: (ev: Event) => void): void ;
    removeListener(type: "ReadRequested", listener: (ev: Event) => void): void ;
    on(type: "ReadRequested", listener: (ev: Event) => void): void ;
    off(type: "ReadRequested", listener: (ev: Event) => void): void ;
    
    addListener(type: "SubscribedClientsChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "SubscribedClientsChanged", listener: (ev: Event) => void): void ;
    on(type: "SubscribedClientsChanged", listener: (ev: Event) => void): void ;
    off(type: "SubscribedClientsChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: "WriteRequested", listener: (ev: Event) => void): void ;
    removeListener(type: "WriteRequested", listener: (ev: Event) => void): void ;
    on(type: "WriteRequested", listener: (ev: Event) => void): void ;
    off(type: "WriteRequested", listener: (ev: Event) => void): void ;
    
    addListener(type: string, listener: (ev: Event) => void): void ;
    removeListener(type: string, listener: (ev: Event) => void): void ;
    on(type: string, listener: (ev: Event) => void): void ;
    off(type: string, listener: (ev: Event) => void): void ;
    

  }

  export class GattLocalDescriptorResult {
    descriptor: GattLocalDescriptor;
    error: Number;
    constructor();

  }

  export class GattLocalDescriptor {
    readProtectionLevel: GattProtectionLevel;
    staticValue: Object;
    uuid: String;
    writeProtectionLevel: GattProtectionLevel;
    constructor();

    addListener(type: "ReadRequested", listener: (ev: Event) => void): void ;
    removeListener(type: "ReadRequested", listener: (ev: Event) => void): void ;
    on(type: "ReadRequested", listener: (ev: Event) => void): void ;
    off(type: "ReadRequested", listener: (ev: Event) => void): void ;
    
    addListener(type: "WriteRequested", listener: (ev: Event) => void): void ;
    removeListener(type: "WriteRequested", listener: (ev: Event) => void): void ;
    on(type: "WriteRequested", listener: (ev: Event) => void): void ;
    off(type: "WriteRequested", listener: (ev: Event) => void): void ;
    
    addListener(type: string, listener: (ev: Event) => void): void ;
    removeListener(type: string, listener: (ev: Event) => void): void ;
    on(type: string, listener: (ev: Event) => void): void ;
    off(type: string, listener: (ev: Event) => void): void ;
    

  }

  export class GattSubscribedClient {
    maxNotificationSize: Number;
    session: GattSession;
    constructor();

    addListener(type: "MaxNotificationSizeChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "MaxNotificationSizeChanged", listener: (ev: Event) => void): void ;
    on(type: "MaxNotificationSizeChanged", listener: (ev: Event) => void): void ;
    off(type: "MaxNotificationSizeChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: string, listener: (ev: Event) => void): void ;
    removeListener(type: string, listener: (ev: Event) => void): void ;
    on(type: string, listener: (ev: Event) => void): void ;
    off(type: string, listener: (ev: Event) => void): void ;
    

  }

  export class GattReadRequestedEventArgs {
    session: GattSession;
    constructor();

    getRequestAsync(callback: (error: Error, result: GattReadRequest) => void): void ;

    getDeferral(): Object;

  }

  export class GattWriteRequestedEventArgs {
    session: GattSession;
    constructor();

    getRequestAsync(callback: (error: Error, result: GattWriteRequest) => void): void ;

    getDeferral(): Object;

  }

  export class GattClientNotificationResult {
    protocolError: Number;
    status: GattCommunicationStatus;
    subscribedClient: GattSubscribedClient;
    constructor();

  }

  export class GattReadRequest {
    length: Number;
    offset: Number;
    state: GattRequestState;
    constructor();

    respondWithValue(value: Object): void;

    respondWithProtocolError(protocolError: Number): void;

    addListener(type: "StateChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "StateChanged", listener: (ev: Event) => void): void ;
    on(type: "StateChanged", listener: (ev: Event) => void): void ;
    off(type: "StateChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: string, listener: (ev: Event) => void): void ;
    removeListener(type: string, listener: (ev: Event) => void): void ;
    on(type: string, listener: (ev: Event) => void): void ;
    off(type: string, listener: (ev: Event) => void): void ;
    

  }

  export class GattRequestStateChangedEventArgs {
    error: Number;
    state: GattRequestState;
    constructor();

  }

  export class GattWriteRequest {
    offset: Number;
    option: GattWriteOption;
    state: GattRequestState;
    value: Object;
    constructor();

    respond(): void;

    respondWithProtocolError(protocolError: Number): void;

    addListener(type: "StateChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "StateChanged", listener: (ev: Event) => void): void ;
    on(type: "StateChanged", listener: (ev: Event) => void): void ;
    off(type: "StateChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: string, listener: (ev: Event) => void): void ;
    removeListener(type: string, listener: (ev: Event) => void): void ;
    on(type: string, listener: (ev: Event) => void): void ;
    off(type: string, listener: (ev: Event) => void): void ;
    

  }

}



