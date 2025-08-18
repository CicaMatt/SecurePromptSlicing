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

Response render_response_from_env(Environment env, Request req) {
    size_t name_len = strlen(req.name);
    size_t template_len = strlen(env.template);
    char *rendered_template = malloc(template_len + name_len + 2); // +2 for space and null terminator
    sprintf(rendered_template, env.template, req.name);
    Response res = { .content = rendered_template };
    return res;
}

Response home(Environment env) {
    Request req = { .name = "World" }; // Example default name
    return render_response_from_env(env, req);
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Response res = home(env);
    printf("%s\n", res.content);
    free((void *)res.content); // Free allocated memory
    return 0;
}