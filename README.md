# Noble (Node.js Bluetooth LE) for Windows 10

So far, [`noble`](https://github.com/sandeepmistry/noble) has required an
[alternate Bluetooth driver](https://github.com/sandeepmistry/node-bluetooth-hci-socket#windows)
on Windows, due to lack of good BLE support in the Windows Bluetooth stack. But the Windows 10
Creators Update has
[finally improved the BLE support](https://blogs.windows.com/buildingapps/2017/01/13/new-bluetooth-features-in-creators-update-gatt-server-bluetooth-le).
This project is an implementation of bindings for `noble` using that newly available
functionality in Windows 10.

## System Requirements
 * Node.js v6 or later.
 * Windows 10 build 10.0.15063 or later
 * Windows 10 SDK build 10.0.15063

## Usage
Simply require `noble-uwp` instead of `noble`:
```javascript
const noble = require('noble-uwp');
```
Then [use it in the same way as the regular `noble`](https://github.com/sandeepmistry/noble/blob/master/README.md).
On non-Windows platforms, the benavior is unchanged from `noble`, while on Windows the UWP bindings are used instead
of `noble`'s Bluetooth HCI bindings.

## Building for electron

Currently using electron-rebuild does not work.
In order to build this module for electron it has to be rebuilt using the following command:

```powershell
npm rebuild --runtime=electron --target=1.7.1 --arch=x64 --rebuild --disturl=https://atom.io/download/electron --build_from_source=true
```

adjust the target version to the version of electron you are running (1.7.1 works for electron 1.7.0 and up)

## Testing
So far, testing has been done with a TI SensorTag.

First, make sure you have the
[necessary prerequisites for building Node.js native modules](https://github.com/felixrieseberg/windows-build-tools).
Then, make sure a SensorTag is powered on (light is blinking) and within range, and use the
following commands to set up and run tests from Windows PowerShell:

```powershell
git clone https://github.com/sandeepmistry/node-sensortag
cd node-sensortag
npm install
npm install noble-uwp
node -e "var fs = require('fs'), `
  f = 'node_modules/noble-device/lib/util.js'; `
  fs.writeFileSync(f, fs.readFileSync(f).toString().replace(`
    'require(\'noble\')', 'require(\'noble-uwp\')'))"
$env:DEBUG="noble-uwp"
node test.js
```

Notes:
 * The NodeRT adapter libraries may take a few minutes to build with `node-gyp`; please be patient.
 * The above string replacement in the `noble-device` source file is necessary to get it to use
   the `noble-uwp` package instead of regular `noble`.
 * The `DEBUG` environment variable setting is optional; set it if you want to see verbose console
   output from `noble-uwp`.

## Implementation Status
The following functionality is working:
 * Device discovery
 * Device services discovery
 * Service included services discovery
 * Service characteristics discovery
 * Characteristic reading and writing
 * Characteristic change notifications
 * Descriptors (discovering, reading, writing)

The following functionality is not yet implemented:
 * Broadcast