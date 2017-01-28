declare module "windows.devices.radios" {
  export enum RadioState {
    unknown,
    on,
    off,
    disabled,
  }

  export enum RadioKind {
    other,
    wiFi,
    mobileBroadband,
    bluetooth,
    fM,
  }

  export enum RadioAccessStatus {
    unspecified,
    allowed,
    deniedByUser,
    deniedBySystem,
  }

  export class Radio {
    kind: RadioKind;
    name: String;
    state: RadioState;
    constructor();

    static getRadiosAsync(callback: (error: Error, result: Object) => void): void ;


    static fromIdAsync(deviceId: String, callback: (error: Error, result: Radio) => void): void ;


    static requestAccessAsync(callback: (error: Error, result: RadioAccessStatus) => void): void ;


    static getDeviceSelector(): String;


    setStateAsync(value: RadioState, callback: (error: Error, result: RadioAccessStatus) => void): void ;

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



