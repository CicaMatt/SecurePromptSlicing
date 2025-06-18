#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "environment.h"

void render_response_from_env(environment* env) {
  char* name = get_name(env);
  char* template = get_template(env);
  char* rendered = render(template, name);
  printf("%s", rendered);
}