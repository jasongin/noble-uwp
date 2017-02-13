using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.Advertisement;
using Windows.Devices.Bluetooth.GenericAttributeProfile;

namespace BluetoothTest
{
    class BluetoothTest
    {
        BluetoothLEAdvertisementWatcher advertisementWatcher;
        TaskCompletionSource<ulong> findAddressTaskCompletionSource;

        public BluetoothTest()
        {
            this.Log = s => { };
        }

        public Action<string> Log { get; set; }

        public Task<ulong> FindSensorTagAddressAsync()
        {
            this.findAddressTaskCompletionSource = new TaskCompletionSource<ulong>();

            this.advertisementWatcher = new BluetoothLEAdvertisementWatcher();
            this.advertisementWatcher.ScanningMode = BluetoothLEScanningMode.Active;
            this.advertisementWatcher.Received += this.OnAdvertisementWatcherReceived;
            this.advertisementWatcher.Stopped += this.OnAdvertisementWatcherStopped;
            this.advertisementWatcher.Start();

            return this.findAddressTaskCompletionSource.Task;
        }

        void OnAdvertisementWatcherStopped(
            BluetoothLEAdvertisementWatcher sender,
            BluetoothLEAdvertisementWatcherStoppedEventArgs args)
        {
            Log($"Watcher stopped: Error = {args.Error}");
        }

        void OnAdvertisementWatcherReceived(
            BluetoothLEAdvertisementWatcher sender,
            BluetoothLEAdvertisementReceivedEventArgs args)
        {
            this.Log($"Watcher received: " +
                $"Address = {args.BluetoothAddress.ToString("X8") }, " +
                $"Name = {args.Advertisement.LocalName}, " +
                $"Advertisement = {args.AdvertisementType}");

            if (args.Advertisement.LocalName.EndsWith("SensorTag"))
            {
                advertisementWatcher.Stop();
                this.findAddressTaskCompletionSource.SetResult(args.BluetoothAddress);
            }
        }

        public async Task QuerySensorTag(ulong bluetoothAddress)
        {
            // Reference: https://www.bluetooth.com/specifications/gatt/services
            // Reference: http://www.ti.com/ww/en/wireless_connectivity/sensortag2015/tearDown.html

            Guid buttonServiceUuid = Guid.Parse("0000ffe0-0000-1000-8000-00805f9b34fb");
            Guid buttonCharacteristicUuid = Guid.Parse("0000ffe1-0000-1000-8000-00805f9b34fb");

            try
            {
                Log("Connecting...");

                // The FromBluetoothAddressAsync() call never invokes the continuation
                // (nor throws an exception) when invoked from a console app.
                BluetoothLEDevice device = await
                    BluetoothLEDevice.FromBluetoothAddressAsync(bluetoothAddress).AsTask();

                Log($"Querying:   {device.Name}");

                foreach (KeyValuePair<string, object> prop in device.DeviceInformation.Properties)
                {
                    Log($"  {prop.Key} = {prop.Value}");
                }

                GattDeviceServicesResult servicesResult =
                    await device.GetGattServicesAsync(BluetoothCacheMode.Uncached);
                Log($"Services:   {servicesResult.Status}");

                foreach (GattDeviceService service in servicesResult.Services)
                {

                    GattCharacteristicsResult characteristicsResult =
                        await service.GetCharacteristicsAsync(BluetoothCacheMode.Uncached);
                    Log($"  Service: {service.Uuid}");

                    foreach (var characteristic in characteristicsResult.Characteristics)
                    {
                        //Log($"    Characteristic: {characteristic.Uuid}");

                        if (characteristic.Uuid == buttonCharacteristicUuid)
                        {
                            // Set the characteristic configuration descriptor to Notify to enable notifications.
                            // Reading and/or writing configuration descriptors gives inconsistent results!!

                            var configValue = await characteristic.ReadClientCharacteristicConfigurationDescriptorAsync();
                            Log("config value: " + configValue.ClientCharacteristicConfigurationDescriptor);

                            await characteristic.WriteClientCharacteristicConfigurationDescriptorAsync(
                                GattClientCharacteristicConfigurationDescriptorValue.None);

                            configValue = await characteristic.ReadClientCharacteristicConfigurationDescriptorAsync();
                            Log("config value: " + configValue.ClientCharacteristicConfigurationDescriptor);

                            await characteristic.WriteClientCharacteristicConfigurationDescriptorAsync(
                                GattClientCharacteristicConfigurationDescriptorValue.Notify);

                            configValue = await characteristic.ReadClientCharacteristicConfigurationDescriptorAsync();
                            Log("config value: " + configValue.ClientCharacteristicConfigurationDescriptor);

                            // Register for change notifications for the "key" characteristic.
                            characteristic.ValueChanged += this.OnValueChanged;

                            Log("Button notifications enabled. Press the button to test!");
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Log("Failed to query sensor tag: " + ex);
            }
        }

        void OnValueChanged(GattCharacteristic sender, GattValueChangedEventArgs args)
        {
            byte[] value = args.CharacteristicValue.ToArray();
            Log("Button pressed!  " + BitConverter.ToString(value));
        }
    }
}
