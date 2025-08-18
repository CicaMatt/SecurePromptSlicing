#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock structures and functions to simulate a web server environment
typedef struct {
    char *name;
} Request;

typedef struct {
    char *template_content;
} Environment;

char* get_parameter(Request *request, const char *param_name) {
    if (strcmp(param_name, "name") == 0) {
        return request->name ? strdup(request->name) : NULL;
    }
    return NULL;
}

Environment* get_environment() {
    // Mock environment
    Environment *env = malloc(sizeof(Environment));
    env->template_content = "Hello, %s!";
    return env;
}

char* render_response_from_env(Request *request, Environment *env) {
    char *name = get_parameter(request, "name");
    if (!name || !env || !env->template_content) {
        return NULL;
    }
    
    // Calculate buffer size
    size_t template_len = strlen(env->template_content);
    size_t name_len = strlen(name);
    char *response = malloc(template_len + name_len + 1); // +1 for null terminator

    if (!response) {
        free(name);
        return NULL;
    }

    snprintf(response, template_len + name_len + 1, env->template_content, name);

    free(name);
    return response;
}

int main() {
    Request request = {.name = "Alice"};
    Environment *env = get_environment();
    
    char *response = render_response_from_env(&request, env);
    if (response) {
        printf("%s\n", response);
        free(response);
    } else {
        printf("Failed to generate response.\n");
    }

    free(env);
    return 0;
}