//#include <node.h>

#include "node-crf.hpp"

#include <string>
#include <cstring>
#include <stdlib.h>

using namespace v8;
//using namespace std;

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
    NODE_SET_PROTOTYPE_METHOD(constructor, "classify", classify);

    // This has to be last, otherwise the properties won't show up on the
    // object in JavaScript.
    target->Set(name, constructor->GetFunction());
}

CRF::CRF(){};

//Utility
char *CRF::get(Local<Value> value, const char *fallback = "") {
    if (value->IsString()) {
        v8::String::Utf8Value string(value->ToString());
        char *str = (char *) malloc(string.length() + 1);
        std::strcpy(str, *string);
        return str;
    }
    char *str = (char *) malloc(std::strlen(fallback) + 1);
    std::strcpy(str, fallback);
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

    CRFPP::Tagger* tag = CRFPP::createTagger(get(args[0]));
    if(!tag){
       return ThrowException(Exception::TypeError(
            String::New(CRFPP::getTaggerError())));
    }

    obj -> tagger = Persistent<CRFPP::Tagger>(tag);

    obj->Wrap(args.This());

    return args.This();
}

Handle<Value> CRF::classify(const Arguments& args){
    HandleScope scope;
    Local<Array> arr = Local<Array>::Cast(args[0]);
    CRF* obj = ObjectWrap::Unwrap<CRF>(args.This());

    CRFPP::Tagger *a = *(obj->tagger);

    a->clear();

    int size = arr->Length();
    for(int i=0;i<size;i++){
        Local<Value> element = arr->Get(i);
        char* c = get(element);
        a->add(c);
        // each iteration, free memory
        free(c);
        c = NULL;
    }

    a->parse();

    Local<Array> solutions = Array::New(a->nbest());
    unsigned int count = 0;
    while (count < a->nbest())
    {
        Local<Array> s = Array::New(a->ysize());
        for (size_t i = 0; i < a->size(); ++i)
        {
            s -> Set(i,Local<Value>(String::New(a->y2(i))));
        }
        solutions -> Set(count, s);
        a->next();
        count++;
    }

    return scope.Close(solutions);
};



void RegisterModule(Handle<Object> target) {
    CRF::Init(target);
}

NODE_MODULE(nodecrf, RegisterModule);
