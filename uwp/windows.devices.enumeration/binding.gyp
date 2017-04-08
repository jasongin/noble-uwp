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
    }
  ]
}