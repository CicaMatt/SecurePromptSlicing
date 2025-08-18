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

Response* render_response_from_env(Environment *env, Request *req) {
    const char *name = req->name;
    const char *template = env->template;
    size_t len = strlen(template) + strlen(name) + 10;
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    Response *res = malloc(sizeof(Response));
    res->content = rendered;
    return res;
}

Response* home(Environment *env) {
    Request req = { .name = "World" };
    return render_response_from_env(env, &req);
}