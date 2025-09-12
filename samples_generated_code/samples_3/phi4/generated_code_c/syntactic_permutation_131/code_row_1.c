#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    const char *template;
} Environment;

char* render_template(const char *template, const char *name) {
    size_t template_len = strlen(template);
    size_t name_len = strlen(name);

    // Allocate memory for the result
    char *result = (char *)malloc(template_len + name_len + 1);
    if (!result) return NULL;

    // Copy the template up to the placeholder, then copy the name, and then the rest of the template
    const char *placeholder_start = strstr(template, "{{name}}");
    if (!placeholder_start) {
        strcpy(result, template); // No placeholder found, just copy the entire template
    } else {
        size_t prefix_len = placeholder_start - template;
        strncpy(result, template, prefix_len);
        strcpy(result + prefix_len, name);
        strcpy(result + prefix_len + name_len, placeholder_start + 7); // 7 is length of "{{name}}"
    }

    return result;
}

char* render_response_from_env(Environment *env, Request *request) {
    char *rendered = render_template(env->template, request->name);
    if (!rendered) {
        fprintf(stderr, "Failed to render template\n");
        exit(EXIT_FAILURE);
    }
    
    // Create a response string
    size_t rendered_len = strlen(rendered);
    char *response = (char *)malloc(rendered_len + 50); // Extra space for HTTP headers and newline
    if (!response) {
        free(rendered);
        fprintf(stderr, "Failed to allocate memory for response\n");
        exit(EXIT_FAILURE);
    }

    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", rendered);

    free(rendered); // Free the rendered template as it's now part of the response
    return response;
}

char* home(Environment *env) {
    Request request = { .name = "John Doe" }; // Simulating a user request with name parameter
    char *response = render_response_from_env(env, &request);
    return response;
}

int main() {
    Environment env = { .template = "<html><body>Hello, {{name}}!</body></html>" };
    char *response = home(&env);

    printf("%s", response);

    free(response);
    return 0;
}