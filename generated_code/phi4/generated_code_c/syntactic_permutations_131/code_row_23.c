#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENV_SIZE 256
#define MAX_TEMPLATE_SIZE 1024

typedef struct {
    char *name;
} Environment;

char* get_template(Environment *env) {
    // Dummy implementation for fetching template from environment
    static const char* template = "Hello, %s!";
    return strdup(template);
}

char* render_response_from_env(Environment *env) {
    char *template = get_template(env);

    if (!template) {
        return NULL;
    }

    char response[MAX_TEMPLATE_SIZE];
    snprintf(response, sizeof(response), template, env->name);

    char *rendered_template = strdup(response);
    free((void*)template); // Free the duplicated template

    return rendered_template;
}

char* home(Environment *env) {
    char *response = render_response_from_env(env);
    
    if (!response) {
        fprintf(stderr, "Error rendering response.\n");
        exit(EXIT_FAILURE);
    }

    return response;
}

int main() {
    Environment env;
    env.name = strdup("World");

    char *result = home(&env);

    printf("%s\n", result);

    free((void*)env.name);
    free(result);

    return 0;
}