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
    const char *name = req->name;
    const char *template = env->template;
    size_t len = strlen(template) + strlen(name) + 10; // Extra for formatting and null terminator
    char *rendered_template = malloc(len);
    snprintf(rendered_template, len, template, name);
    Response res = { .content = rendered_template };
    return res;
}

Response home(Environment *env, Request *req) {
    return render_response_from_env(env, req);
}