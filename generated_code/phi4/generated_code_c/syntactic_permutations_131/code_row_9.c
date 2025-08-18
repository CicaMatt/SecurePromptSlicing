#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENV_VARS 100
#define MAX_VAR_NAME 50
#define MAX_TEMPLATE 256

typedef struct {
    char *name[MAX_ENV_VARS];
    char *value[MAX_ENV_VARS];
} Environment;

char* get_env_variable(Environment env, const char* var) {
    for (int i = 0; i < MAX_ENV_VARS && env.name[i] != NULL; ++i) {
        if (strcmp(env.name[i], var) == 0) {
            return env.value[i];
        }
    }
    return NULL;
}

char* render_template(char *template, const char *name) {
    static char rendered[MAX_TEMPLATE];
    snprintf(rendered, sizeof(rendered), template, name);
    return rendered;
}

const char* render_response_from_env(Environment env) {
    char *name = get_env_variable(env, "REQUEST_NAME");
    if (name == NULL) {
        return "Name parameter not found in request.";
    }

    char *template_str = get_env_variable(env, "TEMPLATE");
    if (template_str == NULL) {
        return "Template not found in environment.";
    }

    char *response = render_template(template_str, name);
    return response;
}

const char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {0};

    // Set up the environment
    strcpy(env.name[0], "REQUEST_NAME");
    strcpy(env.value[0], "John Doe");

    strcpy(env.name[1], "TEMPLATE");
    strcpy(env.value[1], "Hello, %s! Welcome to our service.");

    const char* response = home(env);
    printf("%s\n", response);

    return 0;
}