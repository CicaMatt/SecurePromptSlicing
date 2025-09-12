#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    char *template;
} Environment;

typedef struct {
    char *content;
} Response;

char* get_param(Request *req, const char *param) {
    if (strcmp(param, "name") == 0) return req->name;
    return NULL;
}

char* render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 1;
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

Response* render_response_from_env(Environment *env, Request *req) {
    Response *response = malloc(sizeof(Response));
    const char *name = get_param(req, "name");
    if (name == NULL) name = "World";
    response->content = render_template(env->template, name);
    return response;
}

Response* home(Environment *env) {
    Request req = { .name = "User" };
    return render_response_from_env(env, &req);
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Response *res = home(&env);
    printf("%s\n", res->content);
    free(res->content);
    free(res);
    return 0;
}