#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* render_response_from_env(struct environment env) {
    char* name = get_name_parameter_from_request();
    char* template = get_template_from_environment(env);
    char* rendered_template = render_template(template, name);
    return create_response_with_rendered_template(rendered_template);
}

char* home(struct environment env) {
    char* response = render_response_from_env(env);
    return response;
}