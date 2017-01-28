  
FoundationContract = (function () {
  var cls = function FoundationContract() {
    };
  return cls;
}) ();
exports.FoundationContract = FoundationContract;


  
UniversalApiContract = (function () {
  var cls = function UniversalApiContract() {
    };
  return cls;
}) ();
exports.UniversalApiContract = UniversalApiContract;


_PropertyType = function () {
  this.empty = 0;
  this.uInt8 = 1;
  this.int16 = 2;
  this.uInt16 = 3;
  this.int32 = 4;
  this.uInt32 = 5;
  this.int64 = 6;
  this.uInt64 = 7;
  this.single = 8;
  this.double = 9;
  this.char16 = 10;
  this.boolean = 11;
  this.string = 12;
  this.inspectable = 13;
  this.dateTime = 14;
  this.timeSpan = 15;
  this.guid = 16;
  this.point = 17;
  this.size = 18;
  this.rect = 19;
  this.otherType = 20;
  this.uInt8Array = 21;
  this.int16Array = 22;
  this.uInt16Array = 23;
  this.int32Array = 24;
  this.uInt32Array = 25;
  this.int64Array = 26;
  this.uInt64Array = 27;
  this.singleArray = 28;
  this.doubleArray = 29;
  this.char16Array = 30;
  this.booleanArray = 31;
  this.stringArray = 32;
  this.inspectableArray = 33;
  this.dateTimeArray = 34;
  this.timeSpanArray = 35;
  this.guidArray = 36;
  this.pointArray = 37;
  this.sizeArray = 38;
  this.rectArray = 39;
  this.otherTypeArray = 40;
}
exports.PropertyType = new _PropertyType();

_AsyncStatus = function () {
  this.canceled = 0;
  this.completed = 1;
  this.error = 2;
  this.started = 3;
}
exports.AsyncStatus = new _AsyncStatus();

PropertyValue = (function () {
  var cls = function PropertyValue() {
  };
  

  cls.createEmpty = function createEmpty() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createUInt8 = function createUInt8(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createInt16 = function createInt16(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createUInt16 = function createUInt16(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createInt32 = function createInt32(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createUInt32 = function createUInt32(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createInt64 = function createInt64(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createUInt64 = function createUInt64(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createSingle = function createSingle(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createDouble = function createDouble(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createChar16 = function createChar16(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="String">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createBoolean = function createBoolean(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Boolean">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createString = function createString(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="String">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createInspectable = function createInspectable(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createGuid = function createGuid(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="String">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createDateTime = function createDateTime(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Date">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createTimeSpan = function createTimeSpan(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createPoint = function createPoint(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createSize = function createSize(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createRect = function createRect(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createUInt8Array = function createUInt8Array(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createInt16Array = function createInt16Array(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createUInt16Array = function createUInt16Array(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createInt32Array = function createInt32Array(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createUInt32Array = function createUInt32Array(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createInt64Array = function createInt64Array(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createUInt64Array = function createUInt64Array(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createSingleArray = function createSingleArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createDoubleArray = function createDoubleArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createChar16Array = function createChar16Array(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<String>">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createBooleanArray = function createBooleanArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Boolean>">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createStringArray = function createStringArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<String>">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createInspectableArray = function createInspectableArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Object>">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createGuidArray = function createGuidArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<String>">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createDateTimeArray = function createDateTimeArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Date>">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createTimeSpanArray = function createTimeSpanArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createPointArray = function createPointArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Object>">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createSizeArray = function createSizeArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Object>">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.createRectArray = function createRectArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Object>">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.PropertyValue = PropertyValue;

IStringable = (function () {
  var cls = function IStringable() {
  };
  

  cls.prototype.toString = function toString() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  return cls;
}) ();
exports.IStringable = IStringable;

Deferral = (function () {
  var cls = function Deferral() {
  };
  
var cls = function Deferral(handler) {
};


  cls.prototype.complete = function complete() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.close = function close() {
}


  return cls;
}) ();
exports.Deferral = Deferral;

IAsyncInfo = (function () {
  var cls = function IAsyncInfo() {
    this.errorCode = new Number();
    this.id = new Number();
    this.status = new AsyncStatus();
  };
  

  cls.prototype.cancel = function cancel() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.close = function close() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  return cls;
}) ();
exports.IAsyncInfo = IAsyncInfo;

IAsyncAction = (function () {
  var cls = function IAsyncAction() {
    this.completed = new Object();
  };
  

  cls.prototype.getResults = function getResults() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  return cls;
}) ();
exports.IAsyncAction = IAsyncAction;

IMemoryBufferReference = (function () {
  var cls = function IMemoryBufferReference() {
    this.capacity = new Number();
  };
  

    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.IMemoryBufferReference = IMemoryBufferReference;

IMemoryBuffer = (function () {
  var cls = function IMemoryBuffer() {
  };
  

  cls.prototype.createReference = function createReference() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="IMemoryBufferReference" />
    /// </signature>
    return new IMemoryBufferReference();
  }


  return cls;
}) ();
exports.IMemoryBuffer = IMemoryBuffer;

MemoryBuffer = (function () {
  var cls = function MemoryBuffer() {
  };
  
var cls = function MemoryBuffer(capacity) {
};


  cls.prototype.createReference = function createReference() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="IMemoryBufferReference" />
    /// </signature>
    return new IMemoryBufferReference();
  }


  cls.prototype.close = function close() {
}


  return cls;
}) ();
exports.MemoryBuffer = MemoryBuffer;

WwwFormUrlDecoder = (function () {
  var cls = function WwwFormUrlDecoder() {
  };
  
var cls = function WwwFormUrlDecoder(query) {
};


  cls.prototype.getFirstValueByName = function getFirstValueByName(name) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="name" type="String">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.first = function first() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.getAt = function getAt(index) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="index" type="Number">A param.</param>
    /// <returns type="IWwwFormUrlDecoderEntry" />
    /// </signature>
    return new IWwwFormUrlDecoderEntry();
  }


  cls.prototype.indexOf = function indexOf(value, index) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="IWwwFormUrlDecoderEntry">A param.</param>
    /// <param name="index" type="Number">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  cls.prototype.getMany = function () {
}

  return cls;
}) ();
exports.WwwFormUrlDecoder = WwwFormUrlDecoder;

IWwwFormUrlDecoderEntry = (function () {
  var cls = function IWwwFormUrlDecoderEntry() {
    this.name = new String();
    this.value = new String();
  };
  

  return cls;
}) ();
exports.IWwwFormUrlDecoderEntry = IWwwFormUrlDecoderEntry;

WwwFormUrlDecoderEntry = (function () {
  var cls = function WwwFormUrlDecoderEntry() {
    this.name = new String();
    this.value = new String();
  };
  

  return cls;
}) ();
exports.WwwFormUrlDecoderEntry = WwwFormUrlDecoderEntry;

IGetActivationFactory = (function () {
  var cls = function IGetActivationFactory() {
  };
  

  cls.prototype.getActivationFactory = function getActivationFactory(activatableClassId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="activatableClassId" type="String">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.IGetActivationFactory = IGetActivationFactory;

IPropertyValue = (function () {
  var cls = function IPropertyValue() {
    this.isNumericScalar = new Boolean();
    this.type = new PropertyType();
  };
  

  cls.prototype.getUInt8 = function getUInt8() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.getInt16 = function getInt16() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.getUInt16 = function getUInt16() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.getInt32 = function getInt32() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.getUInt32 = function getUInt32() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.getInt64 = function getInt64() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.getUInt64 = function getUInt64() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.getSingle = function getSingle() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.getDouble = function getDouble() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.getChar16 = function getChar16() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.getBoolean = function getBoolean() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  cls.prototype.getString = function getString() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.getGuid = function getGuid() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.prototype.getDateTime = function getDateTime() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Date" />
    /// </signature>
    return new Date();
  }


  cls.prototype.getTimeSpan = function getTimeSpan() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Number" />
    /// </signature>
    return new Number();
  }


  cls.prototype.getPoint = function getPoint() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.getSize = function getSize() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.getRect = function getRect() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.getUInt8Array = function getUInt8Array(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// </signature>
  }


  cls.prototype.getInt16Array = function getInt16Array(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// </signature>
  }


  cls.prototype.getUInt16Array = function getUInt16Array(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// </signature>
  }


  cls.prototype.getInt32Array = function getInt32Array(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// </signature>
  }


  cls.prototype.getUInt32Array = function getUInt32Array(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// </signature>
  }


  cls.prototype.getInt64Array = function getInt64Array(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// </signature>
  }


  cls.prototype.getUInt64Array = function getUInt64Array(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// </signature>
  }


  cls.prototype.getSingleArray = function getSingleArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// </signature>
  }


  cls.prototype.getDoubleArray = function getDoubleArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// </signature>
  }


  cls.prototype.getChar16Array = function getChar16Array(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<String>">A param.</param>
    /// </signature>
  }


  cls.prototype.getBooleanArray = function getBooleanArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Boolean>">A param.</param>
    /// </signature>
  }


  cls.prototype.getStringArray = function getStringArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<String>">A param.</param>
    /// </signature>
  }


  cls.prototype.getInspectableArray = function getInspectableArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Object>">A param.</param>
    /// </signature>
  }


  cls.prototype.getGuidArray = function getGuidArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<String>">A param.</param>
    /// </signature>
  }


  cls.prototype.getDateTimeArray = function getDateTimeArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Date>">A param.</param>
    /// </signature>
  }


  cls.prototype.getTimeSpanArray = function getTimeSpanArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Number>">A param.</param>
    /// </signature>
  }


  cls.prototype.getPointArray = function getPointArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Object>">A param.</param>
    /// </signature>
  }


  cls.prototype.getSizeArray = function getSizeArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Object>">A param.</param>
    /// </signature>
  }


  cls.prototype.getRectArray = function getRectArray(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Array<Object>">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.IPropertyValue = IPropertyValue;

Uri = (function () {
  var cls = function Uri() {
    this.absoluteUri = new String();
    this.displayUri = new String();
    this.domain = new String();
    this.extension = new String();
    this.fragment = new String();
    this.host = new String();
    this.password = new String();
    this.path = new String();
    this.port = new Number();
    this.query = new String();
    this.queryParsed = new WwwFormUrlDecoder();
    this.rawUri = new String();
    this.schemeName = new String();
    this.suspicious = new Boolean();
    this.userName = new String();
    this.absoluteCanonicalUri = new String();
    this.displayIri = new String();
  };
  
var cls = function Uri(uri) {
      this.absoluteUri = new String();
      this.displayUri = new String();
      this.domain = new String();
      this.extension = new String();
      this.fragment = new String();
      this.host = new String();
      this.password = new String();
      this.path = new String();
      this.port = new Number();
      this.query = new String();
      this.queryParsed = new WwwFormUrlDecoder();
      this.rawUri = new String();
      this.schemeName = new String();
      this.suspicious = new Boolean();
      this.userName = new String();
      this.absoluteCanonicalUri = new String();
      this.displayIri = new String();
};

var cls = function Uri(baseUri, relativeUri) {
      this.absoluteUri = new String();
      this.displayUri = new String();
      this.domain = new String();
      this.extension = new String();
      this.fragment = new String();
      this.host = new String();
      this.password = new String();
      this.path = new String();
      this.port = new Number();
      this.query = new String();
      this.queryParsed = new WwwFormUrlDecoder();
      this.rawUri = new String();
      this.schemeName = new String();
      this.suspicious = new Boolean();
      this.userName = new String();
      this.absoluteCanonicalUri = new String();
      this.displayIri = new String();
};


  cls.prototype.equals = function equals(pUri) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="pUri" type="Object">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  cls.prototype.combineUri = function combineUri(relativeUri) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="relativeUri" type="String">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.toString = function toString() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.unescapeComponent = function unescapeComponent(toUnescape) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="toUnescape" type="String">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  cls.escapeComponent = function escapeComponent(toEscape) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="toEscape" type="String">A param.</param>
    /// <returns type="String" />
    /// </signature>
    return new String();
  }


  return cls;
}) ();
exports.Uri = Uri;

