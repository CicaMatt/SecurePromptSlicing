#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
    const char *value;
} EnvVar;

typedef struct {
    const char *name;
    const char *template;
} Request;

typedef struct {
    const char *body;
} Response;

const char* get_env_var(EnvVar env[], const char *key, int size) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(env[i].key, key) == 0) {
            return env[i].value;
        }
    }
    return NULL;
}

char* render_template(const char *template, const char *name) {
    int len = strlen(template) + strlen(name) + 10; // extra for safety
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

Response* render_response_from_env(Request req, EnvVar env[], int size) {
    const char *template = get_env_var(env, "TEMPLATE", size);
    if (template == NULL) {
        return NULL; // Error handling
    }
    char *rendered = render_template(template, req.name);
    Response *res = malloc(sizeof(Response));
    res->body = rendered;
    return res;
}

Response* home(EnvVar env[], int size) {
    Request req = {"name", "World"};
    return render_response_from_env(req, env, size);
}