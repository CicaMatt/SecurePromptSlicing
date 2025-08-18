#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENV_MAX_SIZE 1024

typedef struct {
    char **variables;
} Environment;

char *get_param(Environment env, const char *name) {
    for (int i = 0; env.variables[i]; ++i) {
        if (strncmp(env.variables[i], name, strlen(name)) == 0 && env.variables[i][strlen(name)] == '=') {
            return env.variables[i] + strlen(name) + 1;
        }
    }
    return NULL;
}

void render_response_from_env(Environment env) {
    char *name_param = get_param(env, "REQUEST_METHOD");
    if (name_param != NULL && strcmp(name_param, "GET") == 0) {
        name_param = get_param(env, "QUERY_STRING");
        if (name_param != NULL) {
            printf("Name parameter: %s\n", name_param);
        }
    }

    char *template_path = get_param(env, "TEMPLATE_PATH");
    if (template_path != NULL) {
        FILE *file = fopen(template_path, "r");
        if (file != NULL) {
            char buffer[1024];
            while (fgets(buffer, sizeof(buffer), file)) {
                printf("%s", buffer);
            }
            fclose(file);
        } else {
            fprintf(stderr, "Failed to open template file: %s\n", template_path);
        }
    }
}

int main() {
    const int env_size = 5;
    char *env_variables[env_size] = {
        "REQUEST_METHOD=GET",
        "QUERY_STRING=name=JohnDoe",
        "TEMPLATE_PATH=./template.txt",
        NULL
    };

    Environment env = { .variables = (char **)env_variables };
    render_response_from_env(env);

    return 0;
}