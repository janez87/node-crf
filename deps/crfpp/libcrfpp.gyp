{
  'variables': { 'target_arch%': 'x64' },
  'target_defaults': {
    'default_configuration': 'Debug',
    'configurations': {
      'Debug': {
        'defines': [ 'DEBUG', '_DEBUG' ],
        'msvs_settings': {
          'VCCLCompilerTool': {
            'RuntimeLibrary': 1, # static debug
          },
        },
      },
      'Release': {
        'defines': [ 'NDEBUG' ],
        'msvs_settings': {
          'VCCLCompilerTool': {
            'RuntimeLibrary': 0, # static release
          },
        },
      }
    },
    'msvs_settings': {
      'VCLinkerTool': {
        'GenerateDebugInformation': 'true',
      },
    },
    'include_dirs': [
      # platform and arch-specific headers
      'config/<(OS)/<(target_arch)'
    ],
    'defines': [
        'PIC',
        'HAVE_CONFIG_H'
    ],
  },
  'targets': [
    # crfpp
    {
      'target_name': 'crfpp',
      'product_prefix': 'lib',
      'type': 'static_library',
      'sources': [
        'libcrfpp.cpp',
        'lbfgs.cpp', 
        'param.cpp',
        'encoder.cpp',
        'feature.cpp',
        'feature_cache.cpp',
        'feature_index.cpp',
        'node.cpp',
        'path.cpp',
        'tagger.cpp',
      ],

      'conditions':[
        ['OS=="mac"',{
          'xcode_settings':{
           'MACOSX_DEPLOYMENT_TARGET': '10.7',
           'OTHER_CFLAGS':[
             '-pthread',
            '-stdlib=libc++',
          ],
        }
      }]
      ]
    },

  ]
}
