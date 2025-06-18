#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "environment.h"
#include "template.h"

char *render_response_from_env(Environment *env) {
  char *name = get_request_parameter("name");
  Template *template = env->get_template();
  char *output = template->render(name);
  return output;
}