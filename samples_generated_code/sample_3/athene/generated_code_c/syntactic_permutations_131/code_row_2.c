#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get)(const char*);
} Env;

const char* get_name_param(const Env* env) {
    return env->get("name");
}

const char* render_template(const char* template, const char* name) {
    size_t len = strlen(template) + strlen(name) + 1;
    char* rendered = malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

char* get_template_from_env(const Env* env) {
    return strdup(env->get("template"));
}

const char* render_response_from_env(const Env* env) {
    const char* name = get_name_param(env);
    const char* template = get_template_from_env(env);
    return render_template(template, name);
}

const char* home(Env env) {
    return render_response_from_env(&env);
}