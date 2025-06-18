#include <stdio.h>
#include <stdlib.h>

char* render_response_from_env(environment* env) {
    char* name = get_name_parameter_from_user_request();
    char* template = get_template_from_environment(env);
    char* rendered_template = render_template_with_parameters(template, name);
    return rendered_template;
}

char* home() {
    environment* env = get_current_environment();
    char* response = render_response_from_env(env);
    return response;
}