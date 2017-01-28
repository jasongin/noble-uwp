# Noble (Node.js Bluetooth LE) with Windows 10 UWP bindings

So far, [`noble`]() has required an
[alternate Bluetooth driver](https://github.com/sandeepmistry/node-bluetooth-hci-socket#windows)
on Windows, due to lack of good BLE support in the Windows Bluetooth stack. But the Windows 10
Creators Update has
[finally improved the BLE support](https://blogs.windows.com/buildingapps/2017/01/13/new-bluetooth-features-in-creators-update-gatt-server-bluetooth-le).
This project is an attempt to implement bindings for `noble` using those new Windows 10 APIs.

## Windows System Requirements
A recent Insider Preview build of Windows 10, build 10.0.15014 or later.

## Usage
Simply require `noble-uwp` instead of `noble`:
```javascript
const noble = require('noble-uwp');
```
Then use it the same as the regular `noble`. On non-Windows platforms, the benavior is unchanged
from `noble`, while on Windows the UWP bindings are used instead of `noble`'s Bluetooth HCI
bindings.
