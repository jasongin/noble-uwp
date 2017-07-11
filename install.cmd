@echo off

call :builduwp Windows.Foundation %1
call :builduwp Windows.Storage.Streams %1
call :builduwp Windows.Devices.Bluetooth %1
call :builduwp Windows.Devices.Bluetooth.Advertisement %1
call :builduwp Windows.Devices.Bluetooth.GenericAttributeProfile %1
call :builduwp Windows.Devices.Enumeration %1
call :builduwp Windows.Devices.Radios %1
goto :eof

:builduwp
echo Installing NodeRT UWP adapter for %1
pushd %~dp0uwp\%1
call node-pre-gyp install --fallback-to-build --msvs_version=2015 %2
if errorlevel 1 exit
echo.
popd
goto :eof
