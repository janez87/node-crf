{
  "targets": [
    {
      "target_name": "nodecrf",
      "sources": [ "src/node-crf.cpp" ],
      "include_dirs":[
        "include"
      ],
      "variables":{
        "LIB_PATH%":""
      },
      "libraries":[
        "-l<(LIB_PATH)crfpp"
      ]
    }
  ]
}
