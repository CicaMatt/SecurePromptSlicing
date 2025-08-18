#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* render_template(const char *name, const char *template) {
    size_t len = snprintf(NULL, 0, "Name: %s\nTemplate: %s", name, template);
    char *response = (char *)malloc(len + 1);
    if (!response) return NULL;
    snprintf(response, len + 1, "Name: %s\nTemplate: %s", name, template);
    return response;
}

const char* render_response_from_env(Environment *env) {
    if (!env || !env->name || !env->template) return "Invalid environment";
    return render_template(env->name, env->template);
}

const char* home() {
    static Environment env = {"John Doe", "Welcome to the website!"};
    return render_response_from_env(&env);
}

int main() {
    const char *response = home();
    printf("%s\n", response);
    return 0;
}