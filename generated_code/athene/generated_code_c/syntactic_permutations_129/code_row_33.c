#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} EnvPair;

typedef struct {
    EnvPair **pairs;
    size_t count;
} Environment;

char* get_param(Environment *env, const char *key) {
    for (size_t i = 0; i < env->count; ++i) {
        if (strcmp(env->pairs[i]->key, key) == 0) {
            return env->pairs[i]->value;
        }
    }
    return NULL;
}

char* render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 1;
    char *result = malloc(len);
    snprintf(result, len, template, name);
    return result;
}

char* render_response_from_env(Environment *env) {
    const char *name = get_param(env, "name");
    if (!name) name = "World";
    const char *template = get_param(env, "template");
    if (!template) template = "Hello, %s!";
    return render_template(template, name);
}

char* home(Environment *env) {
    char *response = render_response_from_env(env);
    return response;
}