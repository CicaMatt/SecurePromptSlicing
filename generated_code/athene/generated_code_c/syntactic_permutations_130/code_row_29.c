#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *template;
} Environment;

typedef struct {
    const char *name;
} Request;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment env, Request req) {
    const char *name = req.name;
    const char *template = env.template;
    size_t template_len = strlen(template);
    size_t name_len = name ? strlen(name) : 0;
    char *rendered = malloc(template_len + name_len + 1);
    strcpy(rendered, template);
    if (name && name_len > 0) {
        strcat(rendered, name);
    }
    Response resp = { .content = rendered };
    return resp;
}

Response home(Environment env) {
    Request req = { .name = "World" }; // Example default name
    return render_response_from_env(env, req);
}

int main() {
    Environment env = { .template = "Hello, " };
    Response resp = home(env);
    printf("%s\n", resp.content);
    free((void *)resp.content);
    return 0;
}