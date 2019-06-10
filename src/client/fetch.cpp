#include "fetch.hpp"
#include <stdio.h>
#include <string.h>
#include <emscripten/fetch.h>

namespace {

struct Handler {
  std::function<void(std::string)> on_response;
};

void OnSuccess(emscripten_fetch_t* fetch) {
  Handler* handler = static_cast<Handler*>(fetch->userData);
  handler->on_response(std::string(fetch->data, fetch->numBytes));
  delete handler;
  emscripten_fetch_close(fetch);
}

} // namespace

void Fetch(const std::string& url, std::function<void(std::string)> response) {
  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);
  std::string("GET").copy(attr.requestMethod, 6);
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
  attr.onsuccess = OnSuccess;
  attr.userData = new Handler{response};
  emscripten_fetch(&attr, url.c_str());
}
