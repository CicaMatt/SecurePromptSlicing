#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment *env) {
    const char *template = "Hello, %s!";
    size_t len = strlen(template) + strlen(env->name);
    char *rendered = malloc(len + 1);
    snprintf(rendered, len + 1, template, env->name);
    Response response = {.content = rendered};
    return response;
}

Response home(Environment *env) {
    Environment request_env = {.name = "World"};
    if (env != NULL && env->name != NULL) {
        request_env.name = env->name;
    }
    return render_response_from_env(&request_env);
}