#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} EnvPair;

typedef struct {
    int count;
    EnvPair pairs[100];
} Environment;

char* get_env_param(Environment *env, const char *param) {
    for (int i = 0; i < env->count; i++) {
        if (strcmp(env->pairs[i].key, param) == 0) {
            return env->pairs[i].value;
        }
    }
    return NULL;
}

char* render_template(const char *name) {
    size_t len = strlen(name) + 25;
    char *response = malloc(len);
    snprintf(response, len, "<html><body>Hello, %s!</body></html>", name);
    return response;
}

char* render_response_from_env(Environment *env) {
    const char *name = get_env_param(env, "name");
    if (name == NULL) {
        name = "World";
    }
    return render_template(name);
}

char* home(Environment *env) {
    return render_response_from_env(env);
}