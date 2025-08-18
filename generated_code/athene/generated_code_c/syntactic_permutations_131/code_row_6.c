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

Response* render_response_from_env(const Request *req, const Environment *env) {
    size_t len = strlen(env->template) + strlen(req->name) + 100; // Extra space for formatting
    char *rendered = malloc(len);
    snprintf(rendered, len, env->template, req->name);

    Response *res = malloc(sizeof(Response));
    res->content = rendered;
    return res;
}

Response* home(const Request *req, const Environment *env) {
    return render_response_from_env(req, env);
}