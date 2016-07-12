#ifndef NODECRF_HPP
#define NODECRF_HPP

#include <node.h>
#include "crfpp.h"
#include <v8.h>
#include <node_object_wrap.h>

class CRF : public node::ObjectWrap {
public:
    static v8::Persistent<v8::Function> constructor;
    static void Init(v8::Local<v8::Object> exports);

    //actual logic
    static void classify(const v8::FunctionCallbackInfo<v8::Value>& args);

protected:
    CRF();

    static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
    
    v8::Persistent<v8::External, v8::CopyablePersistentTraits<v8::External> > tagger;
    
private:
    static char *get(v8::Local<v8::Value> value, const char *fallback);
};

#endif
