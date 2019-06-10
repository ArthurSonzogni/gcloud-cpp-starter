# Copyright 2019 Arthur Sonzogni. All rights reserved.
# Use of this source code is governed by the MIT license that can be found in
# the LICENSE file.

# functions target is completed whenever the "functions" command is available.
find_program(functions-found functions)
if (NOT functions-found)
  add_custom_target(functions COMMAND npm install -g @google-cloud/functions-emulator)
else()
  add_custom_target(functions)
endif()
