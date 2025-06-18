#include "http/cgi.h"
#include <stdlib.h>
#include "template.h"

void render_response_from_env(http_env* env) {
  char* name = http_get_param(env->request, "name");
  char* template = render_template("home", name);
  http_free_env(env);
  return http_create_response(200, "OK", template);
}

http_response* home(http_env* env) {
  http_response* response = render_response_from_env(env);
  return response;
}