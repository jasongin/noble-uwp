declare module "windows.foundation" {
  export class FoundationContract {
    constructor();
  }

  export class UniversalApiContract {
    constructor();
  }

  export enum PropertyType {
    empty,
    uInt8,
    int16,
    uInt16,
    int32,
    uInt32,
    int64,
    uInt64,
    single,
    double,
    char16,
    boolean,
    string,
    inspectable,
    dateTime,
    timeSpan,
    guid,
    point,
    size,
    rect,
    otherType,
    uInt8Array,
    int16Array,
    uInt16Array,
    int32Array,
    uInt32Array,
    int64Array,
    uInt64Array,
    singleArray,
    doubleArray,
    char16Array,
    booleanArray,
    stringArray,
    inspectableArray,
    dateTimeArray,
    timeSpanArray,
    guidArray,
    pointArray,
    sizeArray,
    rectArray,
    otherTypeArray,
  }

  export enum AsyncStatus {
    canceled,
    completed,
    error,
    started,
  }

  export class PropertyValue {
    constructor();

    static createEmpty(): Object;


    static createUInt8(value: Number): Object;


    static createInt16(value: Number): Object;


    static createUInt16(value: Number): Object;


    static createInt32(value: Number): Object;


    static createUInt32(value: Number): Object;


    static createInt64(value: Number): Object;


    static createUInt64(value: Number): Object;


    static createSingle(value: Number): Object;


    static createDouble(value: Number): Object;


    static createChar16(value: String): Object;


    static createBoolean(value: Boolean): Object;


    static createString(value: String): Object;


    static createInspectable(value: Object): Object;


    static createGuid(value: String): Object;


    static createDateTime(value: Date): Object;


    static createTimeSpan(value: Number): Object;


    static createPoint(value: Object): Object;


    static createSize(value: Object): Object;


    static createRect(value: Object): Object;


    static createUInt8Array(value: Array<Number>): Object;


    static createInt16Array(value: Array<Number>): Object;


    static createUInt16Array(value: Array<Number>): Object;


    static createInt32Array(value: Array<Number>): Object;


    static createUInt32Array(value: Array<Number>): Object;


    static createInt64Array(value: Array<Number>): Object;


    static createUInt64Array(value: Array<Number>): Object;


    static createSingleArray(value: Array<Number>): Object;


    static createDoubleArray(value: Array<Number>): Object;


    static createChar16Array(value: Array<String>): Object;


    static createBooleanArray(value: Array<Boolean>): Object;


    static createStringArray(value: Array<String>): Object;


    static createInspectableArray(value: Array<Object>): Object;


    static createGuidArray(value: Array<String>): Object;


    static createDateTimeArray(value: Array<Date>): Object;


    static createTimeSpanArray(value: Array<Number>): Object;


    static createPointArray(value: Array<Object>): Object;


    static createSizeArray(value: Array<Object>): Object;


    static createRectArray(value: Array<Object>): Object;


  }

  export class IStringable {
    constructor();

    toString(): String;

  }

  export class Deferral {
    constructor();
    constructor(handler: Object);

    complete(): void;

    close(): void;
  }

  export class IAsyncInfo {
    errorCode: Number;
    id: Number;
    status: AsyncStatus;
    constructor();

    cancel(): void;

    close(): void;

  }

  export class IAsyncAction {
    completed: Object;
    constructor();

    getResults(): void;

  }

  export class IMemoryBufferReference {
    capacity: Number;
    constructor();

    addListener(type: "Closed", listener: (ev: Event) => void): void ;
    removeListener(type: "Closed", listener: (ev: Event) => void): void ;
    on(type: "Closed", listener: (ev: Event) => void): void ;
    off(type: "Closed", listener: (ev: Event) => void): void ;
    
    addListener(type: string, listener: (ev: Event) => void): void ;
    removeListener(type: string, listener: (ev: Event) => void): void ;
    on(type: string, listener: (ev: Event) => void): void ;
    off(type: string, listener: (ev: Event) => void): void ;
    

  }

  export class IMemoryBuffer {
    constructor();

    createReference(): IMemoryBufferReference;

  }

  export class MemoryBuffer {
    constructor();
    constructor(capacity: Number);

    createReference(): IMemoryBufferReference;

    close(): void;
  }

  export class WwwFormUrlDecoder {
    constructor();
    constructor(query: String);

    getFirstValueByName(name: String): String;

    first(): Object;

    getAt(index: Number): IWwwFormUrlDecoderEntry;

    indexOf(value: IWwwFormUrlDecoderEntry, index: Number): Boolean;

    getMany();
  }

  export class IWwwFormUrlDecoderEntry {
    name: String;
    value: String;
    constructor();

  }

  export class WwwFormUrlDecoderEntry {
    name: String;
    value: String;
    constructor();

  }

  export class IGetActivationFactory {
    constructor();

    getActivationFactory(activatableClassId: String): Object;

  }

  export class IPropertyValue {
    isNumericScalar: Boolean;
    type: PropertyType;
    constructor();

    getUInt8(): Number;

    getInt16(): Number;

    getUInt16(): Number;

    getInt32(): Number;

    getUInt32(): Number;

    getInt64(): Number;

    getUInt64(): Number;

    getSingle(): Number;

    getDouble(): Number;

    getChar16(): String;

    getBoolean(): Boolean;

    getString(): String;

    getGuid(): String;

    getDateTime(): Date;

    getTimeSpan(): Number;

    getPoint(): Object;

    getSize(): Object;

    getRect(): Object;

    getUInt8Array(value: Array<Number>): void;

    getInt16Array(value: Array<Number>): void;

    getUInt16Array(value: Array<Number>): void;

    getInt32Array(value: Array<Number>): void;

    getUInt32Array(value: Array<Number>): void;

    getInt64Array(value: Array<Number>): void;

    getUInt64Array(value: Array<Number>): void;

    getSingleArray(value: Array<Number>): void;

    getDoubleArray(value: Array<Number>): void;

    getChar16Array(value: Array<String>): void;

    getBooleanArray(value: Array<Boolean>): void;

    getStringArray(value: Array<String>): void;

    getInspectableArray(value: Array<Object>): void;

    getGuidArray(value: Array<String>): void;

    getDateTimeArray(value: Array<Date>): void;

    getTimeSpanArray(value: Array<Number>): void;

    getPointArray(value: Array<Object>): void;

    getSizeArray(value: Array<Object>): void;

    getRectArray(value: Array<Object>): void;

  }

  export class Uri {
    absoluteUri: String;
    displayUri: String;
    domain: String;
    extension: String;
    fragment: String;
    host: String;
    password: String;
    path: String;
    port: Number;
    query: String;
    queryParsed: WwwFormUrlDecoder;
    rawUri: String;
    schemeName: String;
    suspicious: Boolean;
    userName: String;
    absoluteCanonicalUri: String;
    displayIri: String;
    constructor();
    constructor(uri: String);
    constructor(baseUri: String, relativeUri: String);

    static unescapeComponent(toUnescape: String): String;


    static escapeComponent(toEscape: String): String;


    equals(pUri: Object): Boolean;

    combineUri(relativeUri: String): Object;

    toString(): String;

  }

}



