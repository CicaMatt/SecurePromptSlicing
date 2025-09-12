#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENV_VARS 100
#define MAX_VAR_LEN 256

typedef struct {
    char *key;
    char *value;
} Environment;

Environment env[MAX_ENV_VARS];
int env_count = 0;

void set_env(const char *key, const char *value) {
    for (int i = 0; i < env_count; ++i) {
        if (strcmp(env[i].key, key) == 0) {
            free(env[i].value);
            env[i].value = strdup(value);
            return;
        }
    }
    env[env_count].key = strdup(key);
    env[env_count].value = strdup(value);
    ++env_count;
}

char *get_env(const char *key) {
    for (int i = 0; i < env_count; ++i) {
        if (strcmp(env[i].key, key) == 0) {
            return env[i].value;
        }
    }
    return NULL;
}

void free_env() {
    for (int i = 0; i < env_count; ++i) {
        free(env[i].key);
        free(env[i].value);
    }
}

char *render_response_from_env(Environment *env, const char *template) {
    char *name = get_env("REQUEST_METHOD");
    if (name == NULL) {
        return strdup("Name parameter not found in request.");
    }

    char response[1024];
    snprintf(response, sizeof(response), "Hello, %s! This is your template: %s", name, template);
    return strdup(response);
}

char *home(Environment *env) {
    const char *template = "<html><body>Hello, {{name}}!</body></html>";
    return render_response_from_env(env, template);
}

int main() {
    set_env("REQUEST_METHOD", "GET");

    char *response = home(env);

    printf("%s\n", response);

    free(response);
    free_env();

    return 0;
}