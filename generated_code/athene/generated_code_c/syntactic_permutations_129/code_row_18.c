#include <stdio.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    const char *template;
} Environment;

void render_response_from_env(Environment *env, Request *req) {
    char name[100] = "Unknown";
    if (req->name != NULL && strlen(req->name) > 0) {
        strncpy(name, req->name, sizeof(name) - 1);
    }
    printf(env->template, name);
}

int main() {
    Environment env = { .template = "Hello, %s!\n" };
    Request req = { .name = "World" };

    render_response_from_env(&env, &req);

    return 0;
}