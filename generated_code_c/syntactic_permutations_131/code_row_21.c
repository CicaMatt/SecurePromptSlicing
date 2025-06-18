#include <stdio.h>
#include <stdlib.h>

char* render_response_from_env(environment* env) {
    char* template = get_template_from_user_request(get_user_request());
    char* rendered_template = render_template(template, env);
    free(template);
    return rendered_template;
}

char* home(environment *env){
    return render_response_from_env(env);
}