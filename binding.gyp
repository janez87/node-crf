{
  "targets": [
    {
      "target_name": "nodecrf",
      "sources": [ "src/node-crf.cpp" ],
      "include_dirs":[
        "include"
      ],
      "variables":{
        "LIB_PATH":""
      },
      "conditions":[
        ['LIB_PATH==""',{
          "libraries":[
            "-lcrfpp",
            "-L/usr/local/lib/"
          ]
        },{
          "libraries":[
            "-L<(LIB_PATH)crfpp"
          ]
        }
        ],['OS=="win"', {
            'cflags': [
              ' ',
            ],
          }, { # OS != "win"
            "cflags": [
              "-fpermissive",
            ]}]
      ]
    }
  ]
}
