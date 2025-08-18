#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a simple struct for environment to mimic request and template storage.
typedef struct {
    char *request;
    char *template;
} Environment;

// Function to simulate extracting "name" parameter from the request.
char* get_name_parameter(const char *request) {
    const char *prefix = "name=";
    if (strncmp(request, prefix, strlen(prefix)) == 0) {
        return strdup(request + strlen(prefix));
    }
    return NULL;
}

// Function to render template with name parameter
char* render_template_with_name(const char *template, const char *name) {
    size_t buffer_size = strlen(template) + strlen(name) + 1; // +1 for '\0'
    char *rendered = (char *)malloc(buffer_size);
    
    if (!rendered) return NULL;

    snprintf(rendered, buffer_size, template, name);

    return rendered;
}

// Function to render response from environment
char* render_response_from_env(Environment *env) {
    char *name_param = get_name_parameter(env->request);
    if (name_param == NULL) {
        return strdup("Name parameter not found.");
    }

    char *rendered_template = render_template_with_name(env->template, name_param);

    free(name_param); // Clean up the duplicated string

    if (!rendered_template) {
        return strdup("Error rendering template.");
    }

    return rendered_template;
}

// Home function that calls render_response_from_env
char* home(Environment *env) {
    char *response = render_response_from_env(env);
    return response;
}

int main() {
    // Create an environment with a request and a template.
    Environment env = {
        .request = "GET / HTTP/1.1\r\nHost: example.com\r\nname=John",
        .template = "Hello, %s!"
    };

    char *response = home(&env);
    printf("%s\n", response);

    free(response); // Clean up the returned string

    return 0;
}