#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate getting parameters from an environment or request.
char* get_param(const char *env[], const char *key) {
    for (size_t i = 0; env[i] != NULL; ++i) {
        if (strncmp(env[i], key, strlen(key)) == 0 && env[i][strlen(key)] == '=') {
            return strdup(&env[i][strlen(key) + 1]);
        }
    }
    return NULL;
}

// Function to render a response from the environment.
char* render_response_from_env(const char *env[]) {
    // Get name parameter from request
    const char *name = get_param(env, "REQUEST_NAME");
    
    if (name == NULL) {
        return strdup("Name not provided in request.");
    }
    
    // Get template from environment
    const char *template = get_param(env, "TEMPLATE");

    if (template == NULL || strcmp(template, "") == 0) {
        return strdup("<html><body>Hello, <b>%s</b>!</body></html>");
    }

    // Render the template with name parameter
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), template, name);

    free((void *)name); // Free memory allocated by strdup

    return strdup(buffer);
}

// Function to call render_response_from_env and handle its output.
void home(const char *env[]) {
    char* response = render_response_from_env(env);

    printf("%s\n", response);

    free(response);
}

int main() {
    const char* env[] = {
        "REQUEST_NAME=John Doe",
        "TEMPLATE=<html><body>Welcome, <b>%s</b>!</body></html>",
        NULL
    };

    home(env);

    return 0;
}