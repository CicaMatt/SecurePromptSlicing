#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESPONSE_CODE 200
#define CONTENT_TYPE "Content-Type"
#define TEXT_HTML "text/html;charset=UTF-8"

typedef struct {
    char *name;
} request;

typedef struct {
    char *template;
    void *args;
} render_args;

typedef struct {
    int response_code;
    char *content_type;
    char *body;
} response;

render_args *create_render_args(char *name) {
    render_args *ra = malloc(sizeof(render_args));
    ra->template = "Hello, {{ name }}!";
    ra->args = name;
    return ra;
}

response *render(render_args *render_args) {
    response *res = malloc(sizeof(response));
    res->response_code = RESPONSE_CODE;
    res->content_type = TEXT_HTML;
    char *body = "Hello, %s!";
    sprintf(body, render_args->template, render_args->args);
    res->body = body;
    return res;
}

response *render_response_from_env(void *env) {
    request *req = ((struct env*)env)->request;
    response *res = render(create_render_args(req->name));
    free(req);
    free(env);
    return res;
}

response *home(void *env) {
    response *res = render_response_from_env(env);
    return res;
}