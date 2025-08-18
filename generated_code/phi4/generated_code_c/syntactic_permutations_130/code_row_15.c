#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENV_VARS 100

typedef struct {
    char **variables;
    int count;
} Environment;

char *get_param(Environment *env, const char *name) {
    for (int i = 0; i < env->count; ++i) {
        if (strncmp(env->variables[i], name "=", strlen(name)) == 0) {
            return &env->variables[i][strlen(name) + 1];
        }
    }
    return NULL;
}

char *render_template(const char *name) {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), "Hello, %s!", name);
    return buffer;
}

void render_response_from_env(Environment *env, const char *response) {
    printf("%s\n", response);
}

const char *home(Environment *env) {
    const char *name = get_param(env, "REQUEST_METHOD");
    if (strcmp(name, "GET") == 0) {
        name = get_param(env, "NAME");
        if (name) {
            char *response = render_template(name);
            render_response_from_env(env, response);
            return response;
        }
    }
    return "No Name Provided";
}

int main() {
    Environment env;
    env.variables = malloc(MAX_ENV_VARS * sizeof(char *));
    env.count = 0;

    // Simulate environment variables
    char *env_vars[MAX_ENV_VARS] = {
        "REQUEST_METHOD=GET",
        "NAME=World"
    };
    
    for (int i = 0; i < MAX_ENV_VARS && env_vars[i]; ++i) {
        env.variables[env.count++] = strdup(env_vars[i]);
    }

    home(&env);

    // Free allocated memory
    for (int i = 0; i < env.count; ++i) {
        free(env.variables[i]);
    }
    free(env.variables);

    return 0;
}