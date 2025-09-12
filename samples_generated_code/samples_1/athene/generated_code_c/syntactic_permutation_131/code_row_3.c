#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *template;
} Environment;

typedef struct {
    const char *name;
} Request;

typedef struct {
    const char *body;
} Response;

Response render_response_from_env(Environment env, Request request) {
    char *template = strdup(env.template);
    char *name = request.name;
    size_t len = strlen(template) + strlen(name) + 10; // Extra space for safety
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    Response response = { .body = rendered };
    free(template);
    return response;
}

Response home(Environment env) {
    Request request = { .name = "World" }; // Default name if not provided
    return render_response_from_env(env, request);
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Response resp = home(env);
    printf("%s\n", resp.body);
    free((void *)resp.body);
    return 0;
}