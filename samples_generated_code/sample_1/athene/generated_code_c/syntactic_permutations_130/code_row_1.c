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

char* get_parameter(const char *key, Environment *env) {
    if (strcmp(key, "name") == 0 && env->request != NULL) {
        return strdup(env->request->name);
    }
    return NULL;
}

const char* get_template(Environment *env) {
    return env->template;
}

char* render_response(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 10; // Extra for safety
    char *response = malloc(len);
    snprintf(response, len, template, name);
    return response;
}

char* render_response_from_env(Environment *env) {
    const char *name = get_parameter("name", env);
    const char *template = get_template(env);
    if (name == NULL) name = "World";
    return render_response(template, name);
}

char* home(Environment *env) {
    return render_response_from_env(env);
}