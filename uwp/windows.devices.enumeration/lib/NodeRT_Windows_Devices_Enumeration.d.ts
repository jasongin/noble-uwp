declare module "windows.devices.enumeration" {
  export class Color {
    constructor();
  }

  export class Rect {
    constructor();
  }

  export enum DevicePickerDisplayStatusOptions {
    none,
    showProgress,
    showDisconnectButton,
    showRetryButton,
  }

  export enum DeviceClass {
    all,
    audioCapture,
    audioRender,
    portableStorageDevice,
    videoCapture,
    imageScanner,
    location,
  }

  export enum DeviceWatcherStatus {
    created,
    started,
    enumerationCompleted,
    stopping,
    stopped,
    aborted,
  }

  export enum Panel {
    unknown,
    front,
    back,
    top,
    bottom,
    left,
    right,
  }

  export enum DeviceInformationKind {
    unknown,
    deviceInterface,
    deviceContainer,
    device,
    deviceInterfaceClass,
    associationEndpoint,
    associationEndpointContainer,
    associationEndpointService,
  }

  export enum DeviceWatcherEventKind {
    add,
    update,
    remove,
  }

  export enum DevicePairingKinds {
    none,
    confirmOnly,
    displayPin,
    providePin,
    confirmPinMatch,
  }

  export enum DevicePairingResultStatus {
    paired,
    notReadyToPair,
    notPaired,
    alreadyPaired,
    connectionRejected,
    tooManyConnections,
    hardwareFailure,
    authenticationTimeout,
    authenticationNotAllowed,
    authenticationFailure,
    noSupportedProfiles,
    protectionLevelCouldNotBeMet,
    accessDenied,
    invalidCeremonyData,
    pairingCanceled,
    operationAlreadyInProgress,
    requiredHandlerNotRegistered,
    rejectedByHandler,
    remoteDeviceHasAssociation,
    failed,
  }

  export enum DeviceUnpairingResultStatus {
    unpaired,
    alreadyUnpaired,
    operationAlreadyInProgress,
    accessDenied,
    failed,
  }

  export enum DevicePairingProtectionLevel {
    default,
    none,
    encryption,
    encryptionAndAuthentication,
  }

  export enum DeviceAccessStatus {
    unspecified,
    allowed,
    deniedByUser,
    deniedBySystem,
  }

  export class DeviceConnectionChangeTriggerDetails {
    deviceId: String;
    constructor();

  }

  export class DevicePickerAppearance {
    title: String;
    selectedForegroundColor: Object;
    selectedBackgroundColor: Object;
    selectedAccentColor: Object;
    foregroundColor: Object;
    backgroundColor: Object;
    accentColor: Object;
    constructor();

  }

  export class DeviceSelectedEventArgs {
    selectedDevice: DeviceInformation;
    constructor();

  }

  export class DeviceDisconnectButtonClickedEventArgs {
    device: DeviceInformation;
    constructor();

  }

  export class DevicePickerFilter {
    supportedDeviceClasses: Object;
    supportedDeviceSelectors: Object;
    constructor();

  }

  export class DevicePicker {
    appearance: DevicePickerAppearance;
    filter: DevicePickerFilter;
    requestedProperties: Object;
    constructor();

    pickSingleDeviceAsync(selection: Object, callback: (error: Error, result: DeviceInformation) => void): void ;
    pickSingleDeviceAsync(selection: Object, placement: Number, callback: (error: Error, result: DeviceInformation) => void): void ;

    show(selection: Object): void;
    show(selection: Object, placement: Number): void;

    hide(): void;

    setDisplayStatus(device: DeviceInformation, status: String, options: DevicePickerDisplayStatusOptions): void;

    addListener(type: "DevicePickerDismissed", listener: (ev: Event) => void): void ;
    removeListener(type: "DevicePickerDismissed", listener: (ev: Event) => void): void ;
    on(type: "DevicePickerDismissed", listener: (ev: Event) => void): void ;
    off(type: "DevicePickerDismissed", listener: (ev: Event) => void): void ;
    
    addListener(type: "DeviceSelected", listener: (ev: Event) => void): void ;
    removeListener(type: "DeviceSelected", listener: (ev: Event) => void): void ;
    on(type: "DeviceSelected", listener: (ev: Event) => void): void ;
    off(type: "DeviceSelected", listener: (ev: Event) => void): void ;
    
    addListener(type: "DisconnectButtonClicked", listener: (ev: Event) => void): void ;
    removeListener(type: "DisconnectButtonClicked", listener: (ev: Event) => void): void ;
    on(type: "DisconnectButtonClicked", listener: (ev: Event) => void): void ;
    off(type: "DisconnectButtonClicked", listener: (ev: Event) => void): void ;
    
    addListener(type: string, listener: (ev: Event) => void): void ;
    removeListener(type: string, listener: (ev: Event) => void): void ;
    on(type: string, listener: (ev: Event) => void): void ;
    off(type: string, listener: (ev: Event) => void): void ;
    

  }

  export class DeviceThumbnail {
    contentType: String;
    size: Number;
    canRead: Boolean;
    canWrite: Boolean;
    position: Number;
    constructor();

    readAsync(buffer: Object, count: Number, options: Number, callback: (error: Error, result: Object) => void): void ;

    writeAsync(buffer: Object, callback: (error: Error, result: Number) => void): void ;

    flushAsync(callback: (error: Error, result: Boolean) => void): void ;

    getInputStreamAt(position: Number): Object;

    getOutputStreamAt(position: Number): Object;

    seek(position: Number): void;

    cloneStream(): Object;

    close(): void;
  }

  export class EnclosureLocation {
    inDock: Boolean;
    inLid: Boolean;
    panel: Panel;
    rotationAngleInDegreesClockwise: Number;
    constructor();

  }

  export class DeviceInformationUpdate {
    id: String;
    properties: Object;
    kind: DeviceInformationKind;
    constructor();

  }

  export class DeviceInformationCollection {
    constructor();

    getAt(index: Number): DeviceInformation;

    indexOf(value: DeviceInformation, index: Number): Boolean;

    getMany();
    first(): Object;

  }

  export class DeviceWatcher {
    status: DeviceWatcherStatus;
    constructor();

    start(): void;

    stop(): void;

    getBackgroundTrigger(requestedEventKinds: Object): Object;

    addListener(type: "Added", listener: (ev: Event) => void): void ;
    removeListener(type: "Added", listener: (ev: Event) => void): void ;
    on(type: "Added", listener: (ev: Event) => void): void ;
    off(type: "Added", listener: (ev: Event) => void): void ;
    
    addListener(type: "EnumerationCompleted", listener: (ev: Event) => void): void ;
    removeListener(type: "EnumerationCompleted", listener: (ev: Event) => void): void ;
    on(type: "EnumerationCompleted", listener: (ev: Event) => void): void ;
    off(type: "EnumerationCompleted", listener: (ev: Event) => void): void ;
    
    addListener(type: "Removed", listener: (ev: Event) => void): void ;
    removeListener(type: "Removed", listener: (ev: Event) => void): void ;
    on(type: "Removed", listener: (ev: Event) => void): void ;
    off(type: "Removed", listener: (ev: Event) => void): void ;
    
    addListener(type: "Stopped", listener: (ev: Event) => void): void ;
    removeListener(type: "Stopped", listener: (ev: Event) => void): void ;
    on(type: "Stopped", listener: (ev: Event) => void): void ;
    off(type: "Stopped", listener: (ev: Event) => void): void ;
    
    addListener(type: "Updated", listener: (ev: Event) => void): void ;
    removeListener(type: "Updated", listener: (ev: Event) => void): void ;
    on(type: "Updated", listener: (ev: Event) => void): void ;
    off(type: "Updated", listener: (ev: Event) => void): void ;
    
    addListener(type: string, listener: (ev: Event) => void): void ;
    removeListener(type: string, listener: (ev: Event) => void): void ;
    on(type: string, listener: (ev: Event) => void): void ;
    off(type: string, listener: (ev: Event) => void): void ;
    

  }

  export class DeviceInformation {
    enclosureLocation: EnclosureLocation;
    id: String;
    isDefault: Boolean;
    isEnabled: Boolean;
    name: String;
    properties: Object;
    kind: DeviceInformationKind;
    pairing: DeviceInformationPairing;
    constructor();

    static createFromIdAsync(deviceId: String, additionalProperties: Object, kind: DeviceInformationKind, callback: (error: Error, result: DeviceInformation) => void): void ;
    static createFromIdAsync(deviceId: String, callback: (error: Error, result: DeviceInformation) => void): void ;
    static createFromIdAsync(deviceId: String, additionalProperties: Object, callback: (error: Error, result: DeviceInformation) => void): void ;


    static findAllAsync(aqsFilter: String, additionalProperties: Object, kind: DeviceInformationKind, callback: (error: Error, result: DeviceInformationCollection) => void): void ;
    static findAllAsync(callback: (error: Error, result: DeviceInformationCollection) => void): void ;
    static findAllAsync(deviceClass: DeviceClass, callback: (error: Error, result: DeviceInformationCollection) => void): void ;
    static findAllAsync(aqsFilter: String, callback: (error: Error, result: DeviceInformationCollection) => void): void ;
    static findAllAsync(aqsFilter: String, additionalProperties: Object, callback: (error: Error, result: DeviceInformationCollection) => void): void ;


    static getAqsFilterFromDeviceClass(deviceClass: DeviceClass): String;


    static createWatcher(aqsFilter: String, additionalProperties: Object, kind: DeviceInformationKind): DeviceWatcher;
    static createWatcher(): DeviceWatcher;
    static createWatcher(deviceClass: DeviceClass): DeviceWatcher;
    static createWatcher(aqsFilter: String): DeviceWatcher;
    static createWatcher(aqsFilter: String, additionalProperties: Object): DeviceWatcher;


    getThumbnailAsync(callback: (error: Error, result: DeviceThumbnail) => void): void ;

    getGlyphThumbnailAsync(callback: (error: Error, result: DeviceThumbnail) => void): void ;

    update(updateInfo: DeviceInformationUpdate): void;

  }

  export class DevicePairingResult {
    protectionLevelUsed: DevicePairingProtectionLevel;
    status: DevicePairingResultStatus;
    constructor();

  }

  export class DeviceUnpairingResult {
    status: DeviceUnpairingResultStatus;
    constructor();

  }

  export class IDevicePairingSettings {
    constructor();

  }

  export class DevicePairingRequestedEventArgs {
    deviceInformation: DeviceInformation;
    pairingKind: DevicePairingKinds;
    pin: String;
    constructor();

    accept(): void;
    accept(pin: String): void;

    getDeferral(): Object;

  }

  export class DeviceInformationCustomPairing {
    constructor();

    pairAsync(pairingKindsSupported: DevicePairingKinds, callback: (error: Error, result: DevicePairingResult) => void): void ;
    pairAsync(pairingKindsSupported: DevicePairingKinds, minProtectionLevel: DevicePairingProtectionLevel, callback: (error: Error, result: DevicePairingResult) => void): void ;
    pairAsync(pairingKindsSupported: DevicePairingKinds, minProtectionLevel: DevicePairingProtectionLevel, devicePairingSettings: IDevicePairingSettings, callback: (error: Error, result: DevicePairingResult) => void): void ;

    addListener(type: "PairingRequested", listener: (ev: Event) => void): void ;
    removeListener(type: "PairingRequested", listener: (ev: Event) => void): void ;
    on(type: "PairingRequested", listener: (ev: Event) => void): void ;
    off(type: "PairingRequested", listener: (ev: Event) => void): void ;
    
    addListener(type: string, listener: (ev: Event) => void): void ;
    removeListener(type: string, listener: (ev: Event) => void): void ;
    on(type: string, listener: (ev: Event) => void): void ;
    off(type: string, listener: (ev: Event) => void): void ;
    

  }

  export class DeviceInformationPairing {
    canPair: Boolean;
    isPaired: Boolean;
    custom: DeviceInformationCustomPairing;
    protectionLevel: DevicePairingProtectionLevel;
    constructor();

    static tryRegisterForAllInboundPairingRequests(pairingKindsSupported: DevicePairingKinds): Boolean;


    pairAsync(callback: (error: Error, result: DevicePairingResult) => void): void ;
    pairAsync(minProtectionLevel: DevicePairingProtectionLevel, callback: (error: Error, result: DevicePairingResult) => void): void ;
    pairAsync(minProtectionLevel: DevicePairingProtectionLevel, devicePairingSettings: IDevicePairingSettings, callback: (error: Error, result: DevicePairingResult) => void): void ;

    unpairAsync(callback: (error: Error, result: DeviceUnpairingResult) => void): void ;

  }

  export class DeviceAccessChangedEventArgs {
    status: DeviceAccessStatus;
    id: String;
    constructor();

  }

  export class DeviceAccessInformation {
    currentStatus: DeviceAccessStatus;
    constructor();

    static createFromId(deviceId: String): DeviceAccessInformation;


    static createFromDeviceClassId(deviceClassId: String): DeviceAccessInformation;


    static createFromDeviceClass(deviceClass: DeviceClass): DeviceAccessInformation;


    addListener(type: "AccessChanged", listener: (ev: Event) => void): void ;
    removeListener(type: "AccessChanged", listener: (ev: Event) => void): void ;
    on(type: "AccessChanged", listener: (ev: Event) => void): void ;
    off(type: "AccessChanged", listener: (ev: Event) => void): void ;
    
    addListener(type: string, listener: (ev: Event) => void): void ;
    removeListener(type: string, listener: (ev: Event) => void): void ;
    on(type: string, listener: (ev: Event) => void): void ;
    off(type: string, listener: (ev: Event) => void): void ;
    

  }

  export class DeviceWatcherEvent {
    deviceInformation: DeviceInformation;
    deviceInformationUpdate: DeviceInformationUpdate;
    kind: DeviceWatcherEventKind;
    constructor();

  }

  export class DeviceWatcherTriggerDetails {
    deviceWatcherEvents: Object;
    constructor();

  }

}



