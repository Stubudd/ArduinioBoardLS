using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Microsoft.Maker.Serial;
using Microsoft.Maker.RemoteWiring;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace Arduino_Test
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public sealed partial class MainPage : Page
	{
		UsbSerial connection;
		RemoteDevice arduino;
		UInt16 lastvalue;

		public MainPage()
		{
			this.InitializeComponent();

			connection = new UsbSerial("VID_2341", "PID_0043");
			arduino = new RemoteDevice(connection);
			connection.ConnectionEstablished += OnConnectionEstablished;
			connection.begin(57600, SerialConfig.SERIAL_8N1);


		}

		private void OnConnectionEstablished()
		{
			// enable the on off buttons
			var action = Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.Normal, new Windows.UI.Core.DispatchedHandler(() = > {
				OnButton.IsEnabled = true;
				OffButton.IsEnabled = true;
			}));
			arduino.pinMode(14, PinMode.ANALOG);
			arduino.AnalogPinUpdatedEvent += MyAnalogPinUpdateCallback;
			Debug.WriteLine(arduino.analogRead(14));
		}

		private void OnButtonClick(object sender, RoutedEventArgs e)
		{
			arduino.digitalWrite(13, PinState.HIGH);
		}

		private void OffButtonClick(object sender, RoutedEventArgs e)
		{
			arduino.digitalWrite(13, PinState.LOW);
		}

		public void MyAnalogPinUpdateCallback(byte pin, UInt16 value)
		{
			if (value - lastvalue >5 || lastvalue - value > 5) {

				Debug.WriteLine("Pin A" + pin + " is now " + value);
				var action = Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.Normal, new Windows.UI.Core.DispatchedHandler(() = > {
					byte num = Convert.ToByte(value / 4);
					Page.Background = new SolidColorBrush(Windows.UI.Color.FromArgb(255, num, num, Convert.ToByte(255 - num)));

				}));
			}
			lastvalue = value;

		}
	}


}
