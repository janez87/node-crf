var _nodecrf = require('./build/Release/nodecrf');

var _crf;

//Constructor
//All the properties besides the model are currently useless (I don't retrieve the advanced statistics)
var CRF = function(model, nbest, deepinfo) {

	if (model === undefined) {
		throw new Error('A path to the model must be specified');
	}

	this.model = model;
	this.nbest = nbest || 2;
	this.deepinfo = deepinfo || true;

	this.isInitialized = false;

	//Separator used to separate the actual word from the POS tag
	this.separator = '_';
};


//Initialize the classficator
//It creates the actual C++ object
//Any changes performed after the invokation of this event are useless
CRF.prototype.init = function() {

	var command = '-m ' + this.model;

	if (this.nbest > 0) {
		command += ' -n' + this.nbest;
	}

	if (this.deepinfo) {
		command += ' -v 2';
	}

	_crf = new _nodecrf.CRF(command);

	this.isInitialized = true;
};

//It peform the classification of the text
//The text must be previously POS tagged and in the form "WordSEPARATORTag WordSEPARATORTag"
//It return the category according to the trained model
CRF.prototype.classify = function(text) {

	if (!this.isInitialized) {
		throw new Error('Call the init() methods before classfying');
	}

	//TODO: regexp matching to verify the format of the text?

	var array = text.split(' ');

	for (var i = 0; i < array.length; i++) {
		array[i] = array[i].replace(this.separator, ' ');
	}

	var classification = _crf.classify(array);

	return classification;

};

module.exports.CRF = CRF;
