#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **headers;
    size_t header_count;
} Environment;

typedef struct {
    const char *name;
} Request;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment env, Request request) {
    // Simulate getting the template from environment
    const char *template = "Hello, %s!";
    
    // Simulate rendering the template with the name parameter from the request
    char buffer[256];
    snprintf(buffer, sizeof(buffer), template, request.name);
    
    Response response;
    response.content = strdup(buffer);  // Use strdup to allocate memory for content
    return response;
}

Response home(Environment env) {
    Request request = { .name = "World" }; // Simulate a name parameter from the user request
    return render_response_from_env(env, request);
}

int main() {
    Environment env = {0};  // Initialize an empty environment

    Response resp = home(env);

    printf("%s\n", resp.content);

    free((void*)resp.content);  // Free the memory allocated by strdup
    return 0;
}