#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

const char* render_template(const char *template, const char *name) {
    if (template == NULL || name == NULL) return "Error: Template or Name is NULL";
    
    size_t buffer_size = strlen(template) + strlen(name) + 1; // +1 for '\0'
    char *response = malloc(buffer_size);
    if (!response) return "Error: Memory allocation failed";

    snprintf(response, buffer_size, template, name);

    return response;
}

const char* render_response_from_env(Environment env) {
    const char *name_param = env.name ? env.name : "";
    const char *rendered_template = render_template(env.template, name_param);
    
    if (strncmp(rendered_template, "Error", 5) == 0) {
        free((void *)rendered_template); // Free memory if allocation failed
        return rendered_template;
    }

    return strdup(rendered_template); // Return a copy of the response
}

const char* home(Environment env) {
    const char *response = render_response_from_env(env);
    
    if (strncmp(response, "Error", 5) == 0) {
        return response; // If there's an error in rendering, return it directly.
    }
    
    return strdup(response); // Return a copy of the rendered template
}

int main() {
    Environment env;
    env.name = "John Doe";
    env.template = "Hello, %s! Welcome to our website.";

    const char *response = home(env);
    printf("%s\n", response);

    free((void *)response); // Free memory allocated by strdup

    return 0;
}