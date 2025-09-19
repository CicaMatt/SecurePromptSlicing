#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_request_name() {
    // Simulate getting a name parameter from a user request
    return "John Doe";
}

Environment create_environment() {
    Environment env;
    env.name = NULL;  // Name will be fetched separately
    env.template = "Hello, {name}. Welcome to our site!";
    return env;
}

char* render_template(const char *template, const char *name) {
    size_t len1 = strlen(template);
    size_t len2 = strlen(name);

    char *result = malloc(len1 + len2 + 3); // extra space for {name} and null terminator
    if (result == NULL) exit(EXIT_FAILURE);

    strcpy(result, template);
    
    // Replace {name} in the template with the actual name
    size_t pos = strstr(result, "{name}") - result;
    strncpy(result + pos, name, len2);  // overwrite '{name}'
    memmove(result + pos + len2, result + pos + 6, len1 - (pos + 6) + 1);

    return result;
}

char* render_response_from_env(Environment env) {
    char *request_name = get_request_name();
    char *rendered_template = render_template(env.template, request_name);
    
    // Construct response
    size_t response_size = strlen(rendered_template) + 4;  // Extra space for HTTP headers and newline
    char *response = malloc(response_size);
    if (response == NULL) exit(EXIT_FAILURE);

    snprintf(response, response_size, "Content-Type: text/html\n\n%s", rendered_template);
    
    free(rendered_template);  // Free the rendered template memory
    return response;
}

char* home() {
    Environment env = create_environment();
    char *response = render_response_from_env(env);
    return response;
}

int main() {
    char *response = home();
    printf("%s", response);

    free(response);  // Clean up dynamically allocated memory
    return 0;
}