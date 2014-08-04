{
  "targets": [
    {
      "target_name": "nodecrf",
      "sources": ["src/node-crf.cpp"],
      "include_dirs":[
        "deps/crfpp"
      ],
      'dependencies': [
        'deps/crfpp/libcrfpp.gyp:crfpp',
      ],

      'conditions':[
        ['OS=="mac"',{
          'xcode_settings':{
           'MACOSX_DEPLOYMENT_TARGET': '10.7',
        }
        }]
      ]
    }
  ]
}
