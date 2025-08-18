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
    const char *content;
} Response;

Response render_response_from_env(Environment env, Request req) {
    const char *name = req.name;
    const char *template = env.template;
    size_t len = strlen(template) + strlen(name) + 10; // Extra space for formatting
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    Response res = { .content = rendered };
    return res;
}

Response home(Environment env) {
    Request req = { .name = "World" };
    return render_response_from_env(env, req);
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Response res = home(env);
    printf("%s\n", res.content);
    free((void *)res.content);
    return 0;
}