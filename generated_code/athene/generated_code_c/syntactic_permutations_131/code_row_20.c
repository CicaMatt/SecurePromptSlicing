#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *template;
} Environment;

typedef struct {
    char *name;
} Request;

typedef struct {
    char *body;
} Response;

char* get_param(Request *req, const char *param_name) {
    if (strcmp(param_name, "name") == 0 && req->name != NULL) {
        return req->name;
    }
    return "";
}

Environment* create_env(const char *template) {
    Environment *env = malloc(sizeof(Environment));
    env->template = strdup(template);
    return env;
}

Response* render_response_from_env(Environment *env, Request *req) {
    Response *res = malloc(sizeof(Response));
    const char *name = get_param(req, "name");
    size_t body_len = strlen(env->template) + strlen(name) + 10;
    res->body = malloc(body_len);
    snprintf(res->body, body_len, env->template, name);
    return res;
}

Response* home(Environment *env, Request *req) {
    return render_response_from_env(env, req);
}

void free_response(Response *res) {
    if (res != NULL) {
        free(res->body);
        free(res);
    }
}

void free_environment(Environment *env) {
    if (env != NULL) {
        free(env->template);
        free(env);
    }
}

int main() {
    Environment *env = create_env("Hello, %s!");
    Request req = { .name = "World" };
    Response *res = home(env, &req);

    printf("%s\n", res->body);

    free_response(res);
    free_environment(env);

    return 0;
}