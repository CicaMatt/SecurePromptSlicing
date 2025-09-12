#include <stdio.h>
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

Response render_response_from_env(Environment env, Request req) {
    char name[100];
    if (req.name != NULL) {
        strncpy(name, req.name, 99);
    } else {
        strcpy(name, "World");
    }
    size_t len = strlen(env.template) + strlen(name) + 1;
    char *rendered = malloc(len);
    snprintf(rendered, len, env.template, name);
    Response res = { .content = rendered };
    return res;
}

Response home(Environment env) {
    Request req = { .name = "John" }; // Example request with a name
    return render_response_from_env(env, req);
}