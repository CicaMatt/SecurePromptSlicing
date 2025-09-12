#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_param)(const char*, const char*);
    const char* (*get_template)(void);
} Environment;

typedef struct {
    char* body;
} Response;

Response render_response_from_env(Environment env) {
    const char* name = env.get_param("request", "name");
    const char* template = env.get_template();
    
    // Simple template rendering logic
    char buffer[256];
    snprintf(buffer, sizeof(buffer), template, name);
    
    Response response;
    response.body = strdup(buffer);
    return response;
}

Response home(Environment env) {
    return render_response_from_env(env);
}

// Mock implementation for demonstration purposes
const char* mock_get_param(const char* request, const char* param) {
    if (strcmp(param, "name") == 0) {
        return "World";
    }
    return "";
}

const char* mock_get_template(void) {
    return "Hello, %s!";
}

int main() {
    Environment env = {mock_get_param, mock_get_template};
    Response response = home(env);
    
    printf("%s\n", response.body);
    free(response.body); // Clean up allocated memory
    
    return 0;
}