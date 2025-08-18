#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_template)(const char*);
} Environment;

typedef struct {
    char* body;
} Response;

Response* create_response(const char* body) {
    Response* response = (Response*)malloc(sizeof(Response));
    response->body = strdup(body);
    return response;
}

void free_response(Response* response) {
    if (response) {
        free(response->body);
        free(response);
    }
}

const char* get_template_from_env(const Environment* env, const char* template_name) {
    return env->get_template(template_name);
}

Response* render_response_from_env(Environment* env, const char* name) {
    const char* template = get_template_from_env(env, "home");
    if (template == NULL) {
        return create_response("Template not found");
    }
    
    // Simple rendering logic assuming the template has a placeholder {{name}}
    char rendered[256];
    snprintf(rendered, sizeof(rendered), template, name);
    
    return create_response(rendered);
}

Response* home(Environment* env, const char* request_name) {
    return render_response_from_env(env, request_name);
}

const char* mock_get_template(const char* template_name) {
    if (strcmp(template_name, "home") == 0) {
        return "Hello, %s!";
    }
    return NULL;
}

int main() {
    Environment env = {mock_get_template};
    
    const char* request_name = "User";
    Response* response = home(&env, request_name);
    
    printf("Response: %s\n", response->body);
    
    free_response(response);
    
    return 0;
}