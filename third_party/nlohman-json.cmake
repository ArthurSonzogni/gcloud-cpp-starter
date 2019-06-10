# Copyright 2019 Arthur Sonzogni. All rights reserved.
# Use of this source code is governed by the MIT license that can be found in
# the LICENSE file.

message(STATUS "Checking for nlohman-json: Please wait")

include(ExternalProject)

FetchContent_Declare(nlohmann_json
  URL https://github.com/nlohmann/json/releases/download/v3.1.2/include.zip
)

FetchContent_Populate(nlohmann_json)

add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE ${nlohmann_json_SOURCE_DIR})

message(STATUS "Checking for nlohman-json: DONE")
