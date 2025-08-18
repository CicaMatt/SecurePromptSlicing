#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_name_from_request(Environment *env) {
    // Simulate getting name parameter from request
    return env->name; 
}

char* get_template_from_environment(Environment *env) {
    // Get template from environment
    return env->template;
}

char* render_template(char *template, char *name) {
    if (template == NULL || name == NULL) return NULL;

    size_t buffer_size = strlen(template) + strlen(name) + 1; // +1 for null terminator
    char *buffer = malloc(buffer_size);
    if (!buffer) return NULL;
    
    snprintf(buffer, buffer_size, template, name);

    return buffer;
}

char* render_response_from_env(Environment *env) {
    char *name = get_name_from_request(env);
    char *template = get_template_from_environment(env);
    char *rendered_template = render_template(template, name);
    
    if (rendered_template == NULL) {
        printf("Error rendering template\n");
        return "Internal Server Error";
    }
    
    free(name); // Simulating cleanup
    free(template); // Simulating cleanup

    char *response = malloc(strlen(rendered_template) + 1);
    strcpy(response, rendered_template);
    
    free(rendered_template);

    return response;
}

char* home(Environment *env) {
    char *response = render_response_from_env(env);
    return response;
}

int main() {
    Environment env;
    env.name = strdup("John Doe"); // Simulating request parameter
    env.template = strdup("<html><body>Hello, %s!</body></html>"); // Template with placeholder
    
    char *response = home(&env);

    printf("%s\n", response);
    
    free(env.name);
    free(env.template);
    free(response);
    
    return 0;
}