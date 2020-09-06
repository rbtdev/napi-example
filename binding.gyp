{
  "targets": [
    {
      "target_name": "addon",
      "cflags": [ "-Wall", "-fexceptions","-pthread", "-std=c++11", "-fPIC", "-ffast-math", "-fpermissive","-frtti" ],
      "cflags_cc": [ "-Wall", "-fexceptions","-pthread", "-std=c++11", "-fPIC", "-ffast-math", "-fpermissive","-frtti" ],
      "sources": [ 
          "./src/index.cpp",
          "./src/compute.cpp"
       ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "<!@(node -p \"require('napi-thread-safe-callback').include\")",
        "./src"
      ],
      "libraries": [],
      "defines": [ "NAPI_CPP_EXCEPTIONS"  ]
    }
  ]
}