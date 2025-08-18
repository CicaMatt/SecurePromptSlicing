#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
} Request;

typedef struct {
    Request request;
    const char* template;
} Environment;

typedef struct {
    const char* body;
} Response;

Response render_response_from_env(Environment env) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), env.template, env.request.name);
    Response response = { .body = strdup(buffer) };
    return response;
}

Response home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Request request = { .name = "World" };
    Environment env = { .request = request, .template = "Hello, %s!" };
    Response response = home(env);

    printf("Response: %s\n", response.body);
    free((void*)response.body); // Free the allocated memory for the response body

    return 0;
}