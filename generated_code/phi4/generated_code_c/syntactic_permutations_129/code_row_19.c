#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock of an environment structure
typedef struct {
    char *name;
    char *template;
} Environment;

// Function to simulate getting a name parameter from request in an environment
char* get_name_parameter(Environment *env) {
    return env->name;
}

// Function to render template and create response
char* render_response_from_env(Environment *env) {
    // Get name parameter (simulated)
    char *name = get_name_parameter(env);
    
    // Get the template from environment
    char *template = env->template;

    // Allocate memory for rendered response (simple substitution example)
    size_t response_size = strlen(name) + strlen(template) + 1;
    char *response = malloc(response_size);

    if (!response) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    snprintf(response, response_size, "%s: %s", name, template);

    return response;
}

// Home function that calls render_response_from_env
char* home(Environment *env) {
    char *response = render_response_from_env(env);
    return response;
}

int main() {
    // Example environment setup
    Environment env;
    env.name = "User123";
    env.template = "Welcome to the site!";

    // Get response from home function
    char *response = home(&env);

    // Output the response
    printf("%s\n", response);

    // Free allocated memory
    free(response);
    
    return 0;
}