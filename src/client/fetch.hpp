// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef FETCH_H
#define FETCH_H

#include <string>
#include <functional>

void Fetch(const std::string& url, std::function<void(std::string)> on_response);

#endif /* end of include guard: FETCH_H */
