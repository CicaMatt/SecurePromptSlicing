#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
} Request;

typedef struct {
    Request* request;
    const char* template;
} Environment;

typedef struct {
    const char* body;
} Response;

Response* render_response_from_env(Environment* env) {
    const char* name = env->request->name;
    const char* template = env->template;

    // Allocate memory for the response body
    size_t body_size = strlen(template) + strlen(name) + 1; // +1 for null terminator
    char* body = (char*)malloc(body_size);
    if (!body) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Render the template with the name parameter
    snprintf(body, body_size, template, name);

    // Create and return the response
    Response* response = (Response*)malloc(sizeof(Response));
    if (!response) {
        free(body);
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    response->body = body;
    return response;
}

void home(Environment* env) {
    Response* response = render_response_from_env(env);
    printf("Response: %s\n", response->body);

    // Clean up
    free((void*)response->body);
    free(response);
}

int main() {
    Request request = {"Alice"};
    Environment env = {&request, "Hello, %s!"};

    home(&env);

    return 0;
}