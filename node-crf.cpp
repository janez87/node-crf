//#include <node.h>

#include "node-crf.hpp"

#include <string>

using namespace v8;
using namespace std;

Persistent<FunctionTemplate> CRF::constructor;

void CRF::Init(Handle<Object> target) {
    HandleScope scope;

    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    Local<String> name = String::NewSymbol("CRF");

    constructor = Persistent<FunctionTemplate>::New(tpl);
    // ObjectWrap uses the first internal field to store the wrapped pointer.
    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(name);

    // Add all prototype methods, getters and setters here.
    NODE_SET_PROTOTYPE_METHOD(constructor, "model", getModel);
    NODE_SET_PROTOTYPE_METHOD(constructor, "classify", classify);

    // This has to be last, otherwise the properties won't show up on the
    // object in JavaScript.
    target->Set(name, constructor->GetFunction());
}

CRF::CRF(){};

//Utility
char *CRF::get(Local<Value> value, const char *fallback = "") {
    if (value->IsString()) {
        v8::String::AsciiValue string(value);
        char *str = (char *) malloc(string.length() + 1);
        strcpy(str, *string);
        return str;
    }
    char *str = (char *) malloc(strlen(fallback) + 1);
    strcpy(str, fallback);
    return str;
}
//###################################################################

Handle<Value> CRF::New(const Arguments& args) {
    HandleScope scope;

    if (!args.IsConstructCall()) {
        return ThrowException(Exception::TypeError(
            String::New("Use the new operator to create instances of this object."))
        );
    }

    if (args.Length() < 1) {
        return ThrowException(Exception::TypeError(
            String::New("First argument must be the path to the model")));
    }

    // Creates a new instance object of this type and wraps it.
    CRF* obj = new CRF();

    //Path to the model file
    obj -> model_ = Persistent<String>::New(args[0]-> ToString());


    CRFPP::Tagger* tag = CRFPP::createTagger(get(args[0]));
    if(!tag){
       return ThrowException(Exception::TypeError(
            String::New(CRFPP::getTaggerError())));
    }

    obj -> tagger = Persistent<CRFPP::Tagger>::Persistent(tag);

    obj->Wrap(args.This());

    return args.This();
}


Handle<Value> CRF::getModel(const Arguments& args) {
    HandleScope scope;

    // Retrieves the pointer to the wrapped object instance.
    CRF* obj = ObjectWrap::Unwrap<CRF>(args.This());

    return scope.Close(obj->model_);
}

Handle<Value> CRF::classify(const Arguments& args){
    HandleScope scope;
    Local<Array> arr = Local<Array>::Cast(args[0]);
    CRF* obj = ObjectWrap::Unwrap<CRF>(args.This());

    CRFPP::Tagger *a = *(obj->tagger);

    a->clear();

    uint size = arr->Length();
    for(uint i=0;i<size;i++){
        Local<Value> element = arr->Get(i);

        printf("%s \n",get(element));
        a->add(get(element));
    }

    a->parse();
    const char* solution = a->y2(0);
    return scope.Close(String::New(solution));
};



void RegisterModule(Handle<Object> target) {
    CRF::Init(target);
}

NODE_MODULE(nodecrf, RegisterModule);