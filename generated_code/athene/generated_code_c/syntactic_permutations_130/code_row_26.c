#include <stdio.h>
#include <string.h>

typedef struct {
    const char *name;
} Request;

typedef struct {
    Request request;
    const char *template;
} Environment;

const char* get_name(Environment env) {
    return env.request.name;
}

const char* get_template(Environment env) {
    return env.template;
}

char* render_template(const char *template, const char *name) {
    static char response[256];
    snprintf(response, sizeof(response), template, name);
    return response;
}

void render_response_from_env(Environment env) {
    const char *name = get_name(env);
    const char *template = get_template(env);
    char *response = render_template(template, name);
    printf("%s\n", response);
}

void home(Environment env) {
    render_response_from_env(env);
}

int main() {
    Environment env = {
        .request = { .name = "World" },
        .template = "Hello, %s!"
    };
    home(env);
    return 0;
}