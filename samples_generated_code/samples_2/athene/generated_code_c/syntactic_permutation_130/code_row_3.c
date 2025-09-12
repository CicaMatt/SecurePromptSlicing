#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Request;

typedef struct {
    Request *request;
    const char *template;
} Environment;

char *render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 10; // Extra for safety
    char *response = malloc(len);
    snprintf(response, len, template, name);
    return response;
}

char *render_response_from_env(Environment *env) {
    const char *name = env->request->name;
    const char *template = env->template;
    return render_template(template, name);
}

char *home(Environment *env) {
    return render_response_from_env(env);
}