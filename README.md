# gcloud-cpp-starter

Start project with:
 * C++ / WebAssembly client / server
 * The client use a C++ virtual dom.
 * The client runs on Google cloud functions.
 * Entirely made with C++ / CMake. Not JavaScript.
 * No dependencies. Simple CMake functions will fetch them if needed.

# How to build?

[![asciicast](https://asciinema.org/a/guUjW9jwA27KDYJTCzjBxLXY2.svg)](https://asciinema.org/a/guUjW9jwA27KDYJTCzjBxLXY2)

* Make sure cmake, emscripten and npm are installed and build:
~~~bash
mkdir build
cd build
emcmake cmake ..
make
make run
~~~

* Deploy the server locally using the emulator:
~~~
make deploy
~~~

* Serve the client locally and open it usint a web browser:
~~~
make run
~~~
