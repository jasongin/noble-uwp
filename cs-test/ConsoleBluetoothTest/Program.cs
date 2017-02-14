using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading;
using System.Threading.Tasks;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.Advertisement;
using Windows.Devices.Bluetooth.GenericAttributeProfile;
using Windows.Foundation;

namespace BluetoothTest
{
    class Program
    {
        static void Main(string[] args)
        {
            ComSecurity.Init();
            AsyncPump.Run(TestAsync);

            // Wait for button press.
            Thread.Sleep(1000000);
        }

        static void Log(string message)
        {
            Console.WriteLine(message);
        }

        static async Task TestAsync()
        {
            BluetoothTest test = new BluetoothTest();
            test.Log = s => Log(s);
            ulong deviceAddress = await test.FindSensorTagAddressAsync();
            await test.QuerySensorTag(deviceAddress);
        }
    }
}
