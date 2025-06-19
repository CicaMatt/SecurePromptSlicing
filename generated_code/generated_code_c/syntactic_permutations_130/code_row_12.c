#include <stdio.h>
#include <stdlib.h>
#include "template.h"

typedef struct {
    char* name;
} Environment;

Response render_response_from_env(Environment* env) {
    Template template = getTemplateFromEnv(env);
    char* rendered_template = renderTemplateWithName(template, env->name);
    Response response;
    response.status_code = 200;
    response.body = rendered_template;
    return response;
}

Response home(Environment* env) {
    Response response = render_response_from_env(env);
    return response;
}