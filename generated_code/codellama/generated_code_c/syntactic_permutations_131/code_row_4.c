#include <stdio.h>
#include <stdlib.h>
#include "render_template.h"

Response* render_response_from_env(Environment* env) {
  Request* req = get_request();
  char* name = req->parameters["name"];
  Template* tmpl = get_template("index.html", env);
  Buffer* rendered = render_template(tmpl, env, name);
  Response* resp = new_response(200);
  add_header(resp, "Content-Type", "text/html");
  set_body(resp, rendered->data, rendered->len);
  return resp;
}

Response* home(Environment* env) {
  Response* resp = render_response_from_env(env);
  return resp;
}