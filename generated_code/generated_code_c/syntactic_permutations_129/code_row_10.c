#include <stdlib.h>
#include <stdio.h>

char *render_response_from_env(environment *env) {
    char *template = env->get_template();
    char *rendered = env->render_template(template);

    return rendered;
}

response *home() {
    environment *env = get_env();
    char *rendered = render_response_from_env(env);

    response *res = new_response(rendered);

    free(rendered);
    return res;
}