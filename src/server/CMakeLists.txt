# Copyright 2019 Arthur Sonzogni. All rights reserved.
# Use of this source code is governed by the MIT license that can be found in
# the LICENSE file.

add_executable(server main.cpp)
set_property(TARGET server PROPERTY CXX_STANDARD 11)
target_link_libraries(server PRIVATE asm-dom)

string(APPEND CMAKE_CXX_FLAGS " -s EXPORTED_FUNCTIONS='[\"_OnRequest\"]'")
string(APPEND CMAKE_CXX_FLAGS " -s EXTRA_EXPORTED_RUNTIME_METHODS='[\"UTF8ToString\", \"stringToUTF8\", \"ccall\"]'")
string(APPEND CMAKE_CXX_FLAGS " -s WASM=1")

# Copy the index.js file into the build directory
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/index.js
  COMMAND cp
  ARGS
    ${CMAKE_CURRENT_SOURCE_DIR}/index.js
    ${CMAKE_CURRENT_BINARY_DIR}/index.js
  MAIN_DEPENDENCY
    ${CMAKE_CURRENT_SOURCE_DIR}/index.js
)
add_custom_target(mv-index-js DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/index.js)
add_dependencies(server mv-index-js)

add_custom_target(deploy
  COMMAND functions config set projectId XXX
  COMMAND functions restart
  COMMAND functions deploy is_prime --trigger-http
  COMMAND functions deploy break_number --trigger-http
  DEPENDS functions
  DEPENDS server
)
