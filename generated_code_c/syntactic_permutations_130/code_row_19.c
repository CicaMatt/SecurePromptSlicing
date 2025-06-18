#include <stdio.h>
#include <stdlib.h>
#include "template.c"
#include "request.c" 
#include "environment.c"
#define RESPONSE_SUCCESS 200

int render_response_from_env(environment *env) {
    char* name = request_get_parameter(env->req, "name");
    template* tmpl = env_get_template(env);
    response* resp = template_render(tmpl, name);
    return RESPONSE_SUCCESS;
}

int home(environment *env) {
    response *resp = render_response_from_env(env);
    return RESPONSE_SUCCESS;
}