{
	'targets': [
		{
			'target_name': 'noble-uwp',
			'dependencies': [
				'uwp/windows.foundation/binding.gyp:binding',
				'uwp/windows.storage.streams/binding.gyp:binding',
				'uwp/windows.devices.bluetooth/binding.gyp:binding',
				'uwp/windows.devices.bluetooth.advertisement/binding.gyp:binding',
				'uwp/windows.devices.bluetooth.genericattributeprofile/binding.gyp:binding',
				'uwp/windows.devices.enumeration/binding.gyp:binding',
				'uwp/windows.devices.radios/binding.gyp:binding',
			],
		},
	],
}
