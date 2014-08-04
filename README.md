node-crf
========

A node wrapper for the CRF++ toolkit

## Attention

This module assume you to have a basic knowledge about CRF, so I suggest you to look at the official site of the original tool ( [CRF++](http://crfpp.googlecode.com/svn/trunk/doc/index.html))

## Requirements

- node-gyp
- A trained CRF++ model
 
## Installation

### From the sources

In the folder run
    
      npm build .

### From npm

     npm install node-crf

## Usage

    // Require the module
    var nodecrf = require('node-crf');
    
    // Create a new classifier object
    // first argument: path to the model file
    // second argument: Nbest value
    // third argument: Deep info
    // NOTE: up to know the module ignore the deep info parameter
    var classifier = new nodecrf.CRF('model', 2, true);
    
    // Specifiy the sperator "WordSEPARATORPostTag"
    classifier.separator = '_';
    
    // Initialize the classifier
    // Any changes done on the object after the invokation of this method will be ignored
    classifier.init();
    
    var text = '2_CD nd_CC part_NN of_IN Web_NNP User_NN Engagement_NN tutorial:_NN Web_NNP Analytics_NNS is_VBZ about_IN to_TO start_VB by_IN @mounialalmas_NNS #www_NN 2013_CD';
    
    // Classify the piece of text
    // It will return an array with the selected (n best) categories for each word
    var solution = classifier.classify(text);
    
    console.log(solution);
    
## Known Issues
- You may need to add config.h to deps/crfpp/config directory according to your platform and arch,
    now we support linux/ia32, linux/x64, mac/x64
- Unresolved compilation issue on Windows (sorry guys, I'm working on that :( )

## Acknowledgments

- Thanks to [Vimos](https://github.com/Vimos) for adding the 'nbest' feature and for "gypifying" the CRF++ library for the module
