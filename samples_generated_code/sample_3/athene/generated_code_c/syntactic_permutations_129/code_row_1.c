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

Response* render_response_from_env(Request *req, Environment *env) {
    if (!env || !req) return NULL;

    size_t len = strlen(env->template) + strlen(req->name) + 100;
    char *rendered_template = malloc(len);
    snprintf(rendered_template, len, env->template, req->name);

    Response *res = malloc(sizeof(Response));
    res->content = rendered_template;

    return res;
}

Response* home(Environment *env) {
    Request req = { .name = "World" };
    return render_response_from_env(&req, env);
}