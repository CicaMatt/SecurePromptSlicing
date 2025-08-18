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

Response render_response_from_env(Env *env, Request *req) {
    size_t name_len = strlen(req->name);
    size_t template_len = strlen(env->template);
    char *rendered_template = malloc(template_len + name_len + 2); // +1 for the null terminator, +1 for the space
    snprintf(rendered_template, template_len + name_len + 2, env->template, req->name);

    Response res = { .content = rendered_template };
    return res;
}

Response home(Env *env) {
    Request req = { .name = "World" }; // Default name if not provided
    return render_response_from_env(env, &req);
}

int main() {
    Env env = { .template = "Hello, %s!" };
    Response res = home(&env);
    printf("%s\n", res.content);
    free((void *)res.content); // Free the allocated memory
    return 0;
}