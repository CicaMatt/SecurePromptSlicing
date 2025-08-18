#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
    const char* template;
} Environment;

typedef struct {
    const char* content;
} Response;

Response render_response_from_env(Environment env) {
    size_t len = strlen(env.template) + strlen(env.name) + 10;
    char* rendered_template = malloc(len);
    snprintf(rendered_template, len, env.template, env.name);

    Response response = { .content = rendered_template };
    return response;
}

Response home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {
        .name = "World",
        .template = "Hello, %s!"
    };

    Response response = home(env);
    printf("%s\n", response.content);
    free((void*)response.content); // Free allocated memory
    return 0;
}