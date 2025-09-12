#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_parameter)(const char* param_name);
} Request;

typedef struct {
    const char* (*get_template)(void);
    void (*render)(const char* template, const char* name);
} Environment;

char* render_response_from_env(Environment env, Request req) {
    const char* name = req.get_parameter("name");
    const char* template = env.get_template();
    
    // Assuming the rendered response can be at most 1024 characters long
    char* response = (char*)malloc(1024 * sizeof(char));
    if (!response) {
        return NULL;
    }
    
    env.render(template, name);
    snprintf(response, 1024, "Rendered with template: %s and name: %s", template, name);
    
    return response;
}

// Mock implementations for testing
const char* mock_get_parameter(const char* param_name) {
    if (strcmp(param_name, "name") == 0) {
        return "John Doe";
    }
    return NULL;
}

const char* mock_get_template(void) {
    return "<html><body>Hello, {{name}}!</body></html>";
}

void mock_render(const char* template, const char* name) {
    printf("Rendering template: %s with name: %s\n", template, name);
}

int main() {
    Request req = {mock_get_parameter};
    Environment env = {mock_get_template, mock_render};

    char* response = render_response_from_env(env, req);
    if (response) {
        printf("Response: %s\n", response);
        free(response);
    }

    return 0;
}