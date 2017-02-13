using System;
using Windows.UI.Core;
using Windows.UI.Xaml.Controls;


namespace BluetoothTest
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            Test();
        }

        async void Log(string line)
        {
            await this.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
            {
                this.log.Document.Selection.TypeText(line + '\n');
            });
        }

        async void Test()
        {
            BluetoothTest test = new BluetoothTest();
            test.Log = s => Log(s);
            ulong deviceAddress = await test.FindSensorTagAddressAsync();
            await test.QuerySensorTag(deviceAddress);
        }
    }
}
