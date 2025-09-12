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
    char *name = (char *)malloc(100);
    strncpy(name, req->name, 99);
    name[99] = '\0';

    size_t len = strlen(env->template) + strlen(name) + 2;
    char *content = malloc(len);
    snprintf(content, len, env->template, name);

    Response res = { .content = content };
    return res;
}

Response home(Environment *env) {
    Request req = { .name = "World" }; // Example default name
    return render_response_from_env(env, &req);
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Response res = home(&env);
    printf("%s\n", res.content);

    free((void *)res.content);
    return 0;
}