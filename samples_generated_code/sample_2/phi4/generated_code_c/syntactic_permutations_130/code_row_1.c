#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated environment for demonstration purposes
typedef struct {
    char *name;
    char *template;
} Environment;

// Function to render response based on environment
char* render_response_from_env(Environment env) {
    if (env.name == NULL || env.template == NULL) {
        return "Error: Missing name or template";
    }
    
    // Allocate memory for the rendered response
    size_t rendered_length = strlen(env.template) + strlen(env.name) + 1;
    char *rendered_response = malloc(rendered_length);
    if (rendered_response == NULL) {
        return "Error: Memory allocation failed";
    }

    // Render template with name parameter
    snprintf(rendered_response, rendered_length, env.template, env.name);

    return rendered_response;
}

// Home function that utilizes render_response_from_env
char* home(Environment env) {
    char *response = render_response_from_env(env);
    
    // Free the allocated memory for response after use (in real-world scenarios, manage this properly)
    free(response); 
    return render_response_from_env(env);
}

int main() {
    // Example environment setup
    Environment env;
    env.name = "John Doe";
    env.template = "Hello, %s! Welcome to our website.";

    char *response = home(env);

    printf("%s\n", response);
    
    free(response);  // Free the memory allocated by render_response_from_env

    return 0;
}