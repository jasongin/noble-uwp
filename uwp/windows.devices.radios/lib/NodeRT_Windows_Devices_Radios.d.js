_RadioState = function () {
  this.unknown = 0;
  this.on = 1;
  this.off = 2;
  this.disabled = 3;
}
exports.RadioState = new _RadioState();

_RadioKind = function () {
  this.other = 0;
  this.wiFi = 1;
  this.mobileBroadband = 2;
  this.bluetooth = 3;
  this.fM = 4;
}
exports.RadioKind = new _RadioKind();

_RadioAccessStatus = function () {
  this.unspecified = 0;
  this.allowed = 1;
  this.deniedByUser = 2;
  this.deniedBySystem = 3;
}
exports.RadioAccessStatus = new _RadioAccessStatus();

Radio = (function () {
  var cls = function Radio() {
    this.kind = new RadioKind();
    this.name = new String();
    this.state = new RadioState();
  };
  

  cls.prototype.setStateAsync = function setStateAsync(value, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="RadioState">A param.</param>
    /// </signature>
  }


  cls.getRadiosAsync = function getRadiosAsync(callback) {
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



  cls.requestAccessAsync = function requestAccessAsync(callback) {
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


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.Radio = Radio;

