#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a simple environment structure
typedef struct {
    char **headers;
    size_t num_headers;
} Environment;

// Function to simulate getting the value of a header
char* get_header_value(Environment *env, const char *header_name) {
    for (size_t i = 0; i < env->num_headers; ++i) {
        if (strncmp(env->headers[i], header_name, strlen(header_name)) == 0 && env->headers[i][strlen(header_name)] == ':') {
            return &env->headers[i][strlen(header_name) + 1];
        }
    }
    return NULL;
}

// Function to simulate rendering a template with the given name
char* render_template(const char *template, const char *name) {
    size_t buffer_size = strlen(template) + strlen(name) + 50; // Extra space for safety
    char *buffer = malloc(buffer_size);
    if (!buffer) return NULL;

    snprintf(buffer, buffer_size, template, name);

    return buffer;
}

// Function to generate response from environment
char* render_response_from_env(Environment *env) {
    const char *template_str = "Hello, %s!";
    
    // Retrieve the value of the 'name' parameter from headers (simulated)
    char *name = get_header_value(env, "Name:");
    if (!name) return strdup("Error: Name not provided");

    // Render the template with the name
    char *rendered_template = render_template(template_str, name);
    if (!rendered_template) return strdup("Error: Template rendering failed");

    return rendered_template;
}

// Home function that returns response from render_response_from_env
char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    // Simulate an environment with a header "Name: John"
    char *headers[] = {"Name: John"};
    Environment env = {headers, 1};

    // Get response from the home function
    char *response = home(&env);

    printf("Response:\n%s\n", response);

    free(response);
    return 0;
}