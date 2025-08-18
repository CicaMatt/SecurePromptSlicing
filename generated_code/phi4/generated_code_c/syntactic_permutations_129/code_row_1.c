#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    Request request;
} Environment;

char* get_template_from_env(Environment *env) {
    // Example template
    return "Hello, %s!";
}

void render_response_from_env(Environment *env, char **response) {
    const char *template = get_template_from_env(env);
    if (template == NULL) {
        *response = strdup("Error: Template not found.");
        return;
    }
    
    // Get name parameter from request
    const char *name = env->request.name ? env->request.name : "Guest";

    // Render the template with the name parameter
    size_t buffer_size = snprintf(NULL, 0, template, name) + 1; 
    *response = (char *)malloc(buffer_size);
    snprintf(*response, buffer_size, template, name);
}

char* home(Environment env) {
    char *response;
    render_response_from_env(&env, &response);
    return response;
}

int main() {
    Environment env;
    Request req;

    // Set the name parameter
    req.name = "Alice";
    env.request = req;

    // Call the home function and get the response
    char *result = home(env);

    // Print the result
    printf("%s\n", result);

    // Free allocated memory
    free(result);

    return 0;
}