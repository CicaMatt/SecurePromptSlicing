#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* render_response_from_env(Environment *env) {
    if (env == NULL || env->name == NULL || env->template == NULL) {
        return strdup("Error: Missing environment data");
    }

    // Allocate memory for the response, assuming a max length of 256 characters
    char *response = malloc(256);
    if (response == NULL) {
        return strdup("Error: Memory allocation failed");
    }

    // Render template with name parameter
    snprintf(response, 256, env->template, env->name);

    return response;
}

char* home(Environment *env) {
    char *response = render_response_from_env(env);
    return response;
}

int main() {
    Environment env;
    env.name = "World";
    env.template = "Hello, %s!";

    char *response = home(&env);
    printf("%s\n", response);

    // Free allocated memory
    free(response);

    return 0;
}