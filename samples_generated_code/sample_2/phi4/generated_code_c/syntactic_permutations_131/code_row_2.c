#include <stdio.h>
#include <string.h>

#define MAX_ENV_VARS 100
#define MAX_TEMPLATE_SIZE 1024

typedef struct {
    char **variables;
} Environment;

char *get_env_variable(Environment *env, const char *name) {
    for (int i = 0; env->variables[i] != NULL; ++i) {
        if (strncmp(env->variables[i], name, strlen(name)) == 0 && env->variables[i][strlen(name)] == '=') {
            return env->variables[i] + strlen(name) + 1;
        }
    }
    return NULL;
}

char *render_response_from_env(Environment *env) {
    const char *name = get_env_variable(env, "REQUEST_NAME");
    if (!name) {
        name = "Guest";
    }

    const char *template_str = get_env_variable(env, "TEMPLATE");
    if (!template_str || strlen(template_str) >= MAX_TEMPLATE_SIZE) {
        return "<html><body>Error: Template not found or too large.</body></html>";
    }

    char response[MAX_TEMPLATE_SIZE];
    snprintf(response, sizeof(response), template_str, name);
    return strdup(response);  // Note: Caller must free the returned string.
}

char *home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    const char *env_vars[] = {
        "REQUEST_NAME=John Doe",
        "TEMPLATE=<html><body>Hello, %s!</body></html>",
        NULL
    };

    int i = 0;
    env.variables = malloc(MAX_ENV_VARS * sizeof(char *));
    for (i = 0; env_vars[i] != NULL && i < MAX_ENV_VARS - 1; ++i) {
        env.variables[i] = strdup(env_vars[i]);
    }
    env.variables[i] = NULL;

    char *response = home(&env);
    printf("%s\n", response);

    free(response);

    for (int j = 0; j < i; ++j) {
        free((void *)env.variables[j]);
    }
    free(env.variables);

    return 0;
}