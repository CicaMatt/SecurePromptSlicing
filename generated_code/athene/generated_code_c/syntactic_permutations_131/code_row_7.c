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

Response render_response_from_env(Environment *env, Request *req) {
    size_t len = strlen(env->template) + strlen(req->name) + 10;
    char *rendered = malloc(len);
    snprintf(rendered, len, env->template, req->name);
    Response res = { .content = rendered };
    return res;
}

Response home(Environment *env) {
    Request req = { .name = "User" }; // Example request with a default name
    return render_response_from_env(env, &req);
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Response res = home(&env);
    printf("%s\n", res.content);
    free((void *)res.content); // Free allocated memory
    return 0;
}