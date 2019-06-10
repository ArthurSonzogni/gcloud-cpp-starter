# Copyright 2019 Arthur Sonzogni. All rights reserved.
# Use of this source code is governed by the MIT license that can be found in
# the LICENSE file.

cmake_minimum_required (VERSION 3.11)
project(asm-dom-cmake
  LANGUAGES CXX
  VERSION 0.1.0
)

string(APPEND CMAKE_CXX_FLAGS " -s EXTRA_EXPORTED_RUNTIME_METHODS='UTF8ToString'")
string(APPEND CMAKE_CXX_FLAGS " -s WASM=1")

add_subdirectory(third_party)
add_subdirectory(src)

add_custom_target(run
  COMMAND google-chrome http://localhost:8888/index.html
  COMMAND cd ${CMAKE_BINARY_DIR}/src/client/ && python -m SimpleHTTPServer 8888
  DEPENDS client
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
  string(APPEND CMAKE_CXX_FLAGS " -Os --js-opts 3 --llvm-lto 3 --llvm-opts 3 --closure 1")
endif()
