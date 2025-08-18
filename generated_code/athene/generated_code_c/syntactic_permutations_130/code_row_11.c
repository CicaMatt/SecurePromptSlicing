#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
    const char *template;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment env) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), env.template, env.name);
    Response response = { .content = strdup(buffer) };
    return response;
}

Response home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "World", .template = "Hello, %s!" };
    Response resp = home(env);
    printf("%s\n", resp.content);
    free((void *)resp.content); // Free the allocated memory
    return 0;
}