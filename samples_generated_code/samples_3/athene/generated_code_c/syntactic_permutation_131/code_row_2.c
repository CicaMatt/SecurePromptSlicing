#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Request;

typedef struct {
    const char *template;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Request req, Environment env) {
    size_t len = strlen(env.template) + strlen(req.name) + 100; // Extra space for formatting
    char *rendered_template = malloc(len);
    snprintf(rendered_template, len, env.template, req.name);
    Response resp = { .content = rendered_template };
    return resp;
}

Response home(Environment env) {
    Request req = { .name = "User" }; // Example name, can be set dynamically
    return render_response_from_env(req, env);
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Response resp = home(env);
    printf("%s\n", resp.content);
    free((void *)resp.content); // Free allocated memory
    return 0;
}