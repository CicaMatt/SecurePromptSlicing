#include <stdio.h>
#include <stdlib.h>
#include "templates/home.html"


char* render_response_from_env(Env* env) {
    char* name = get_name_parameter_from_user_request();
    char* template = get_template_from_environment(env);
    char* rendered = render_template_with_name(template, name);
    return rendered;
}

char* home(Env* env) {
    char* response = render_response_from_env(env);
    return response;
}