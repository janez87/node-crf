node-crf
========

A node wrapper for the CRF++ toolkit

## Attention

This module assume you to have a basic knowledge about CRF, so I suggest you to look at the official site of the original tool ( [CRF++](http://crfpp.googlecode.com/svn/trunk/doc/index.html))

## Requirements

- node-gyp
- CRF++ installed on your system (look [here](http://crfpp.googlecode.com/svn/trunk/doc/index.html))
- A trained CRF++ model
 
## Installation

### From the sources

In the folder run
    
      npm build .

You can specify the localtion of the CRF++ library using the argument --LIB_PATH

      npm build . --LIB_PATH=absolute-path-to-the-folder

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

- Possible compilation problem caused by the location of the `crfpp` library
- Unresolved compilation issue on Windows (sorry guys, I'm working on that :( )

## Acknowledgments

- Thanks to [Vimos](https://github.com/Vimos) for adding the 'nbest' feature
