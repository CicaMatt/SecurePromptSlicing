#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_request_param)(const char* param_name);
    const char* (*get_template)(void);
} Environment;

const char* render_response_from_env(Environment env) {
    const char* name = env.get_request_param("name");
    const char* template = env.get_template();
    
    if (!name || !template) {
        return "Error: Missing name or template.";
    }

    // Simple rendering logic, assuming template is a format string
    size_t response_length = strlen(template) + strlen(name) + 1;
    char* response = (char*)malloc(response_length);
    if (!response) {
        return "Error: Memory allocation failed.";
    }
    
    snprintf(response, response_length, template, name);

    return response;
}

// Mock implementations for the environment functions
const char* mock_get_request_param(const char* param_name) {
    if (strcmp(param_name, "name") == 0) {
        return "John Doe";
    }
    return NULL;
}

const char* mock_get_template(void) {
    return "Hello, %s!";
}

int main() {
    Environment env = {mock_get_request_param, mock_get_template};
    const char* response = render_response_from_env(env);
    
    printf("%s\n", response);

    // Free the allocated memory for the response
    free((void*)response);

    return 0;
}