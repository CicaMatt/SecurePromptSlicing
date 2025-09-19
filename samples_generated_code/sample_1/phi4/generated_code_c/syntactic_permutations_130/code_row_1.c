#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENV_VARS 10
#define MAX_VAR_NAME_LEN 50
#define MAX_VAR_VALUE_LEN 100

typedef struct {
    char name[MAX_VAR_NAME_LEN];
    char value[MAX_VAR_VALUE_LEN];
} EnvVar;

typedef struct {
    EnvVar env_vars[MAX_ENV_VARS];
    int count;
} Environment;

Environment* create_environment() {
    Environment *env = (Environment*)malloc(sizeof(Environment));
    env->count = 0;
    return env;
}

void add_env_var(Environment *env, const char *name, const char *value) {
    if (env->count < MAX_ENV_VARS) {
        strncpy(env->env_vars[env->count].name, name, MAX_VAR_NAME_LEN - 1);
        strncpy(env->env_vars[env->count].value, value, MAX_VAR_VALUE_LEN - 1);
        env->count++;
    }
}

const char* get_env_var(Environment *env, const char *name) {
    for (int i = 0; i < env->count; i++) {
        if (strncmp(env->env_vars[i].name, name, MAX_VAR_NAME_LEN) == 0) {
            return env->env_vars[i].value;
        }
    }
    return NULL;
}

char* render_response_from_env(Environment *env) {
    const char *template = get_env_var(env, "TEMPLATE");
    const char *name = get_env_var(env, "NAME");

    if (template == NULL || name == NULL) {
        return strdup("Error: Missing TEMPLATE or NAME in environment.");
    }

    size_t response_size = strlen(template) + strlen(name) + 1;
    char *response = (char*)malloc(response_size);
    snprintf(response, response_size, template, name);

    return response;
}

char* home(Environment *env) {
    char *response = render_response_from_env(env);
    return response;
}

int main() {
    Environment *env = create_environment();
    add_env_var(env, "NAME", "Alice");
    add_env_var(env, "TEMPLATE", "Hello, %s!");

    char *response = home(env);
    printf("%s\n", response);

    free(response);
    free(env);
    return 0;
}