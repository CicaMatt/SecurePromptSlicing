#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    Request *request;
    const char *template;
} Environment;

typedef struct {
    char *content;
} Response;

Response* render_response_from_env(Environment *env) {
    char *name = env->request->name;
    const char *template = env->template;
    size_t len = strlen(template) + strlen(name) + 10;
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    Response *response = malloc(sizeof(Response));
    response->content = rendered;
    return response;
}

Response* home(Environment *env) {
    return render_response_from_env(env);
}