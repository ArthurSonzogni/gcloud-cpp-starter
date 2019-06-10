// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

server = require('./server.js')

const methods = [
  'break_number',
  'is_prime',
];

for (const method of methods) {
  exports[method] = function(req, res) {
    let result = server.ccall( 'OnRequest', 'string',
                              ['string', 'string', 'string'],
                              [method  , req.path, req.body]);
    res.set('Access-Control-Allow-Origin', '*')
    res.set('Access-Control-Allow-Methods', 'GET')
    res.send(result);
  }
}
