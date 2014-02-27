#ifndef NODECRF_HPP
#define NODECRF_HPP

#include <node.h>
#include "../include/crfpp.h"

class CRF : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);

    //actual logic
    static v8::Handle<v8::Value> classify(const v8::Arguments& args);

protected:
    CRF();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);

    //Actual tagger
    v8::Persistent<CRFPP::Tagger> tagger;
private:
    static char *get(v8::Local<v8::Value> value, const char *fallback);
};

#endif
