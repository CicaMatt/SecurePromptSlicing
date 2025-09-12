#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Request;

typedef struct {
    const char *template;
} Env;

typedef struct {
    const char *content;
} Response;

Response* render_response_from_env(Env *env, Request *req) {
    size_t name_len = strlen(req->name);
    size_t template_len = strlen(env->template);
    char *rendered = malloc(template_len + name_len + 1);
    snprintf(rendered, template_len + name_len + 1, env->template, req->name);
    Response *res = malloc(sizeof(Response));
    res->content = rendered;
    return res;
}

Response* home(Env *env) {
    Request req = {"World"};
    return render_response_from_env(env, &req);
}

int main() {
    Env env = { "Hello, %s!" };
    Response *res = home(&env);
    printf("%s\n", res->content);
    free((char *)res->content);
    free(res);
    return 0;
}