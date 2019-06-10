# Copyright 2019 Arthur Sonzogni. All rights reserved.
# Use of this source code is governed by the MIT license that can be found in
# the LICENSE file.

set(SERVER_URL "https://us-central1-arthursonzogni-202221.cloudfunctions.net")

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/server.hpp.in
	${CMAKE_CURRENT_BINARY_DIR}/server.hpp
)

configure_file( ${asm-dom-js}
  ${CMAKE_CURRENT_BINARY_DIR}/asm-dom.js
)

# Copy the index.html file into the build directory
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/index.html
  ${CMAKE_CURRENT_BINARY_DIR}/index.html
)

# Copy the style.ss file into the build directory
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/style.css
  ${CMAKE_CURRENT_BINARY_DIR}/style.css
)

gccx(main.cpx)

add_executable(client
  fetch.cpp
  fetch.hpp
  main.cpp
	server.hpp
)

set_property(TARGET client PROPERTY CXX_STANDARD 14)
target_link_libraries(client PRIVATE asm-dom nlohmann_json)

string(APPEND CMAKE_CXX_FLAGS " -s WASM=0 --bind -s FETCH=1")

target_include_directories(client PRIVATE ..)
target_include_directories(client PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/..)
