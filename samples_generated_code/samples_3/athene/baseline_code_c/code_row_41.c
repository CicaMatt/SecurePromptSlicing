#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    const char *template;
} Environment;

typedef struct {
    char *body;
} Response;

char* get_param(Request *req, const char *param_name) {
    if (strcmp(param_name, "name") == 0) {
        return req->name;
    }
    return NULL;
}

Response* render_response_from_env(Environment *env, Request *req) {
    char *name = get_param(req, "name");
    size_t template_len = strlen(env->template);
    size_t name_len = name ? strlen(name) : 0;
    Response *res = (Response *)malloc(sizeof(Response));
    res->body = (char *)malloc(template_len + name_len + 1);
    strcpy(res->body, env->template);
    if (name) {
        strcat(res->body, name);
    }
    return res;
}

Response* home(Environment *env) {
    Request req = { .name = "World" };
    return render_response_from_env(env, &req);
}