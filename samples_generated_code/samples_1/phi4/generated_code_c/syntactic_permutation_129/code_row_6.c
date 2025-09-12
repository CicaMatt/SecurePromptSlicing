#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **variables;
} Environment;

char* get_parameter(Environment *env, const char *name) {
    for (size_t i = 0; env->variables[i] != NULL; i++) {
        if (strncmp(env->variables[i], name, strlen(name)) == 0 && 
            env->variables[i][strlen(name)] == '=') {
            return &env->variables[i][strlen(name) + 1];
        }
    }
    return NULL;
}

char* render_template(const char *name) {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), "Rendered template: %s", name);
    return buffer;
}

char* render_response_from_env(Environment *env) {
    const char *name = get_parameter(env, "name");
    if (name == NULL) {
        return "Parameter 'name' not found";
    }
    return render_template(name);
}

char* home() {
    Environment env = { .variables = (char*[]){"name=example", NULL} };
    return render_response_from_env(&env);
}

int main() {
    char *response = home();
    printf("%s\n", response);
    return 0;
}