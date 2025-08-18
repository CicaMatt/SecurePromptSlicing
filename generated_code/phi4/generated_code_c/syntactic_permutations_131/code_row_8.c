#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} request_t;

typedef struct {
    const char *template;
} environment_t;

const char* get_template(environment_t env) {
    return env.template;
}

char* render_template(const char *template, const char *name) {
    size_t buffer_size = snprintf(NULL, 0, template, name) + 1;
    char *buffer = malloc(buffer_size);
    if (buffer) {
        snprintf(buffer, buffer_size, template, name);
    }
    return buffer;
}

char* render_response_from_env(environment_t env, request_t req) {
    const char *template = get_template(env);
    char *response = render_template(template, req.name);
    return response;
}

const char* home(environment_t env, request_t req) {
    char *response = render_response_from_env(env, req);
    printf("%s\n", response);
    free(response);
    return response;
}

int main() {
    environment_t env = { .template = "Hello, %s!" };
    request_t req = { .name = "World" };

    home(env, req);

    return 0;
}