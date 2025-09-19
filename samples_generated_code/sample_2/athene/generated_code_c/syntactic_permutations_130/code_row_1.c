#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
    const char *template;
} Environment;

char *render_response_from_env(Environment *env) {
    char *response = malloc(1024);
    if (env->name == NULL) env->name = "World";
    snprintf(response, 1024, env->template, env->name);
    return response;
}

char *home(Environment *env) {
    Environment request_env = {.name = getenv("NAME"), .template = env->template};
    return render_response_from_env(&request_env);
}