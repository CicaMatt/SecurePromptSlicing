#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_parameter(Environment *env, const char *param_name) {
    if (strcmp(param_name, "name") == 0) {
        return env->name;
    }
    return NULL;
}

char* render_template(const char *template, const char *name) {
    static char result[256];
    snprintf(result, sizeof(result), template, name);
    return result;
}

const char* get_template(Environment *env) {
    return env->template;
}

char* render_response_from_env(Environment *env) {
    char *name = get_parameter(env, "name");
    const char *template = get_template(env);
    if (name && template) {
        return render_template(template, name);
    }
    return NULL;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"Alice", "Hello, %s!"};
    char *response = home(&env);
    if (response) {
        printf("%s\n", response);
    } else {
        printf("Failed to render response.\n");
    }
    return 0;
}