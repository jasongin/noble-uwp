@echo off

call :builduwp Windows.Foundation
call :builduwp Windows.Storage.Streams
call :builduwp Windows.Devices.Bluetooth
call :builduwp Windows.Devices.Bluetooth.Advertisement
call :builduwp Windows.Devices.Bluetooth.GenericAttributeProfile
call :builduwp Windows.Devices.Enumeration
call :builduwp Windows.Devices.Radios
goto :eof

:builduwp
echo Building NodeRT UWP adapter for %1
pushd uwp\%1
call node-gyp rebuild --msvs_version=2015
if errorlevel 1 exit
echo.
popd
goto :eof
