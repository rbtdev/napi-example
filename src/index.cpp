#include <napi.h>
#include "napi-thread-safe-callback.hpp"

// Function declaration for compute task
#include "compute.h"

#define CONST_STRING "This is a constant string"
#define CONST_NUMBER 1234
#define OBJ_PROP1_NAME "prop1"
#define OBJ_PROP2_NAME "prop2"
#define OBJ_PROP1_VALUE "This is a string property"
#define OBJ_PROP2_VALUE 123456

//Prototype of functions called by node consumer
extern Napi::Object _initialize(Napi::Env env, Napi::Object exports);
extern Napi::Value run(const Napi::CallbackInfo &info);

//Initialize instance
Napi::Object _initialize(Napi::Env env, Napi::Object exports)
{
  // Set exported properties (methods and/or constants)
  // Methods
  exports.Set("run", Napi::Function::New(env, run));

  // Constants
  exports.Set("CONST_STRING", Napi::String::New(env, CONST_STRING));
  exports.Set("CONST_NUMBER", Napi::Number::New(env, CONST_NUMBER));
  // Create an object to export
  Napi::Object obj = Napi::Object::New(env);
  obj.Set(OBJ_PROP1_NAME, OBJ_PROP1_VALUE);
  obj.Set(OBJ_PROP2_NAME, OBJ_PROP2_VALUE);
  exports.Set("CONST_OBJ", obj);

  return exports;
} 

//
// Method implementation
//
Napi::Value run(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  // Get first argument
  double data = (double)info[0].ToNumber();

  // Get second argument as callback function
  auto callback = std::make_shared<ThreadSafeCallback>(info[1].As<Napi::Function>());

  // Pass arguments to other thread
  std::thread([callback, data] {
    try
    {
      // Run a CPU instensive task here (on a separate thread)
      double result = compute(data);

      // callback(undefined, result)
      callback->call([result](Napi::Env env, std::vector<napi_value> &args) {
        args = {env.Undefined(), Napi::Number::New(env, result)};
      });
    }
    catch (std::exception &e)
    {
      // callback(err);
      callback->callError(e.what());
    }
  }).detach();

  return env.Null();
}

// Set init method for module
NODE_API_MODULE(NODE_GYP_MODULE_NAME, _initialize)