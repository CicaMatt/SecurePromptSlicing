#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENV_VAR_NAME "TEMPLATE_NAME"
#define DEFAULT_TEMPLATE "default_template.txt"

typedef struct {
    char **variables;
} Environment;

char *get_template_name(Environment *env) {
    for (int i = 0; env->variables[i] != NULL; i++) {
        if (strncmp(env->variables[i], ENV_VAR_NAME "=", strlen(ENV_VAR_NAME) + 1) == 0) {
            return env->variables[i] + strlen(ENV_VAR_NAME) + 1;
        }
    }
    return DEFAULT_TEMPLATE;
}

char *render_template(const char *template_name) {
    FILE *file = fopen(template_name, "r");
    if (!file) {
        file = fopen(DEFAULT_TEMPLATE, "r");
        if (!file) {
            perror("Error opening template file");
            exit(EXIT_FAILURE);
        }
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char *content = malloc(length + 1);
    if (!content) {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(content, 1, length, file);
    content[length] = '\0';
    fclose(file);

    return content;
}

char *render_response_from_env(Environment *env) {
    const char *template_name = get_template_name(env);
    return render_template(template_name);
}

char *home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { (char*[]){"TEMPLATE_NAME=welcome.txt", NULL} };
    char *response = home(&env);

    printf("%s\n", response);
    free(response);

    return 0;
}