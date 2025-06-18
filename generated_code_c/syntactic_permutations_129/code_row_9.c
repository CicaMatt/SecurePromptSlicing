#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *render_response_from_env(struct environment *env) {
    struct request *request = env->request;
    char *name = request->parameters["name"];
    struct template *template = env->get_template("index");
    char *rendered = template->render(name);
    return rendered;
}

char *home(struct environment *env) {
    char *response = render_response_from_env(env);
    return response;
}