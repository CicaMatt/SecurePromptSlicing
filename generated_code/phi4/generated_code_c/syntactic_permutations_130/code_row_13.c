#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Environment;

char* get_template(Environment *env) {
    return "Hello, %s!";
}

char* render_response_from_env(Environment *env) {
    if (!env || !env->name) {
        return strdup("Invalid environment or name parameter.");
    }

    const char *template = get_template(env);
    size_t buffer_size = strlen(template) + strlen(env->name) + 1;
    char *response = (char *)malloc(buffer_size);

    snprintf(response, buffer_size, template, env->name);
    return response;
}

char* home(Environment *env) {
    if (!env) {
        return strdup("Invalid environment.");
    }
    return render_response_from_env(env);
}

int main() {
    Environment env = { "World" };
    char *response = home(&env);
    printf("%s\n", response);
    free(response);

    // Test with invalid environment
    Environment invalid_env;
    response = home(&invalid_env);
    printf("%s\n", response);
    free(response);

    return 0;
}