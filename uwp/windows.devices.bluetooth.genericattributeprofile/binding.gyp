{
  'includes': [ '../../common.gypi' ],
  "targets": [
    {
      "target_name": "binding",
      "sources": [ "_nodert_generated.cpp",
                  "NodeRtUtils.cpp",
                  "OpaqueWrapper.cpp",
                  "CollectionsConverterUtils.cpp"],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      'libraries': [ '-lruntimeobject.lib'],
      'configurations': {
        'Debug': {
          'msvs_settings': {
            'VCCLCompilerTool': {
              'AdditionalOptions': ['/bigobj'],
            }
          },
        },
      },
    },
    {
      'target_name': 'action_after_build',
      'type': 'none',
      'dependencies': [ '<(module_name)' ],
      'copies': [
        {
          'files': [ '<(PRODUCT_DIR)/<(module_name).node' ],
          'destination': '<(module_path)'
        }
      ]
	}
  ]
}