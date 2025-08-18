#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **headers;
    int header_count;
} Environment;

typedef struct {
    char *key;
    char *value;
} RequestParameter;

// Function to simulate retrieving a parameter from the request environment.
const char* get_request_parameter(Environment *env, const char *param_name) {
    for (int i = 0; i < env->header_count; ++i) {
        if (strncmp(env->headers[i], param_name, strlen(param_name)) == 0 && env->headers[i][strlen(param_name)] == '=') {
            return env->headers[i] + strlen(param_name) + 1;
        }
    }
    return NULL;
}

// Function to simulate retrieving a template from the environment.
const char* get_template_from_env(Environment *env, const char *template_name) {
    // For simplicity, just returning a fixed template string.
    if (strcmp(template_name, "greeting") == 0) {
        return "<h1>Hello, %s!</h1>";
    }
    return NULL;
}

// Function to render the response from environment.
char* render_response_from_env(Environment *env) {
    const char *name = get_request_parameter(env, "name");
    if (!name || strlen(name) == 0) {
        name = "Guest";
    }

    const char *template = get_template_from_env(env, "greeting");
    if (!template) return strdup("Template not found");

    size_t buffer_size = snprintf(NULL, 0, template, name) + 1;
    char *response = (char*)malloc(buffer_size);
    snprintf(response, buffer_size, template, name);

    return response;
}

// The home function to demonstrate usage.
void home() {
    Environment env;
    const char *headers[] = {"name=John Doe"};
    env.headers = headers;
    env.header_count = sizeof(headers) / sizeof(headers[0]);

    char *response = render_response_from_env(&env);
    printf("%s\n", response);

    free(response);
}

int main() {
    home();
    return 0;
}