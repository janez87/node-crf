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
            "-lcrfpp"
          ]
        },{
          "libraries":[
            "-L<(LIB_PATH)crfpp"
          ]
        }
        ],['OS=="win"', {
            'cflags': [
              '/WX',
            ],
          }, { # OS != "win"
            "cflags": [
              "-fpermissive",
            ]}]
      ]
    }
  ]
}
