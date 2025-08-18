#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char* (*get)(const char*);
} Environment;

const char* get_template(Environment *env, const char* name) {
    return env->get(name);
}

char* render_template(const char* template_str, const char* name) {
    size_t len = strlen(template_str) + strlen(name) + 1;
    char *response = malloc(len);
    snprintf(response, len, template_str, name);
    return response;
}

char* render_response_from_env(Environment *env) {
    const char* name = env->get("name");
    const char* template_str = env->get("template");
    return render_template(template_str, name);
}

char* home(Environment *env) {
    return render_response_from_env(env);
}