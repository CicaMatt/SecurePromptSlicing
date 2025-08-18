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
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), env->template, req->name);
    return (Response){ .content = strdup(buffer) };
}

Response home(Environment *env) {
    Request req = { .name = "World" }; // Default name
    return render_response_from_env(env, &req);
}