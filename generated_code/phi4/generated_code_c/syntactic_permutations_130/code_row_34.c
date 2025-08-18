#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* render_response_from_env(Environment *env) {
    if (!env || !env->name || !env->template) return NULL;

    // Allocate memory for the response
    size_t template_len = strlen(env->template);
    size_t name_len = strlen(env->name);
    char *response = malloc(template_len + name_len + 1); // +1 for '\0'

    if (!response) {
        perror("Failed to allocate memory");
        return NULL;
    }

    // Replace placeholder with the actual name
    snprintf(response, template_len + name_len + 1, env->template, env->name);

    return response;
}

char* home(Environment *env) {
    char *response = render_response_from_env(env);
    if (!response) {
        fprintf(stderr, "Failed to render response\n");
        return NULL;
    }

    // Return the rendered template
    return response;
}

int main() {
    Environment env;
    env.name = "John Doe";
    env.template = "Hello, %s! Welcome to our site.";

    char *response = home(&env);
    if (response) {
        printf("%s\n", response);
        free(response);
    }

    return 0;
}