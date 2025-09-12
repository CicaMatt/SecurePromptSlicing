#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **variables;
} Environment;

char* get_parameter(Environment *env, const char *key) {
    for (int i = 0; env->variables[i] != NULL; i++) {
        if (strncmp(env->variables[i], key, strlen(key)) == 0 && env->variables[i][strlen(key)] == '=') {
            return &env->variables[i][strlen(key) + 1];
        }
    }
    return "";
}

char* get_template(Environment *env) {
    for (int i = 0; env->variables[i] != NULL; i++) {
        if (strncmp(env->variables[i], "template", strlen("template")) == 0 && env->variables[i][strlen("template")] == '=') {
            return &env->variables[i][strlen("template") + 1];
        }
    }
    return "";
}

char* render_response_from_env(Environment *env) {
    char *name = get_parameter(env, "name");
    char *template_str = get_template(env);
    
    if (name[0] == '\0' || template_str[0] == '\0') {
        return strdup("Error: Name or Template not provided.");
    }

    char *rendered = malloc(strlen(template_str) + strlen(name) + 1);
    sprintf(rendered, "%s%s", template_str, name);

    return rendered;
}

char* home(Environment *env) {
    char *response = render_response_from_env(env);
    return response;
}

int main() {
    Environment env;
    const char *variables[] = {"name=John", "template=Hello, ", NULL};
    env.variables = (char **)variables;

    char *response = home(&env);
    printf("%s\n", response);

    free(response);
    return 0;
}