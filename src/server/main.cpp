// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <sstream>

struct Request {
  std::string method;
  std::string path;
  std::string body;
};

int to_int(std::string number) {
  int n = 0;
  std::istringstream(number) >> n;
  return n;
}

// -----------------------------------------------------------------------------

void break_number(int number, int* a, int* b) {
  int divider = std::sqrt(number);
  while (number % divider)
    divider--;
  *a = number / divider;
  *b = divider;
}

std::string break_number_handler(const Request& request) {
  int n = to_int(request.path.substr(1, -1));
  int a, b;
  break_number(n, &a, &b);
  return "[" + std::to_string(a) + "," + std::to_string(b) + "]";
}

// -----------------------------------------------------------------------------

bool is_prime(int number) {
  for (int a = 2; a * a <= number; ++a) {
    if (number % a == 0)
      return false;
  }
  return true;
}

std::string is_prime_handler(const Request& request) {
  int n = to_int(request.path.substr(1, -1));
  return is_prime(n) ? "true" : "false";
}

// -----------------------------------------------------------------------------

using Method = std::function<std::string(Request)>;
std::map<std::string, Method> methods;

void MapMethod() {
  static bool done = false;
  if (done)
    return;

  methods["break_number"] = &break_number_handler;
  methods["is_prime"] = &is_prime_handler;
}

const char* OnRequestCpp(const Request& request) {
  MapMethod();

  if (methods.count(request.method) == 0)
    return "method not found.";

  try {
    return methods[request.method](request).c_str();
  } catch (...) {
    return "error";
  }
}

extern "C" const char* OnRequest(const char* method,
                                 const char* path,
                                 const char* body) {
  Request request;
  request.method = method;
  request.path = path;
  request.body = body;
  return OnRequestCpp(request);
}
