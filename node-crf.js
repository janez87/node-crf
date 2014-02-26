var _nodecrf = require('./build/Release/nodecrf');

var _crf;

var CRF = function(model, nbest, deepinfo) {

	if (model === undefined) {
		throw new Error('A path to the model must be specified');
	}
	this.model = model;
	this.nbest = nbest || 2;
	this.deepInfo = deepinfo || true;

	this.isInitialized = false;

	this.separator = '';
};


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

CRF.prototype.classify = function(text) {

	if (!this.isInitialized) {
		throw new Error('Call the init() methods before classfying');
	}

	var array = text.split(' ');

	for (var i = 0; i < array.length; i++) {
		array[i] = array[i].replace(this.separator, ' ');
	}

	var classification = _crf.classify(array);

	return classification;

};

module.exports.CRF = CRF;