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
    } 
  ]
}
