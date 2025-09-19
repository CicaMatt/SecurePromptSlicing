#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
} Request;

typedef struct {
    const char* template;
} Environment;

typedef struct {
    const char* body;
} Response;

Response render_response_from_env(Environment env, Request request) {
    const char* template = env.template;
    const char* name = request.name;
    size_t len = strlen(template) + strlen(name);
    char* rendered_template = malloc(len + 1);

    if (rendered_template == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    snprintf(rendered_template, len + 1, template, name);

    Response response = { .body = rendered_template };
    return response;
}

Response home(Environment env) {
    Request request = { .name = "World" }; // Example name parameter
    return render_response_from_env(env, request);
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Response response = home(env);

    printf("Response: %s\n", response.body);
    free((void*)response.body); // Free allocated memory

    return 0;
}