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
    char name[100];
    if (req->name != NULL) {
        strncpy(name, req->name, 99);
    } else {
        strcpy(name, "World");
    }
    size_t len = strlen(env->template) + strlen(name) + 1;
    char *rendered = malloc(len);
    snprintf(rendered, len, env->template, name);
    Response resp = { .content = rendered };
    return resp;
}

Response home(Environment *env) {
    Request req = { .name = "User" }; // Example request with a name
    return render_response_from_env(env, &req);
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Response resp = home(&env);
    printf("%s\n", resp.content);
    free((void *)resp.content); // Free allocated memory for the response content
    return 0;
}