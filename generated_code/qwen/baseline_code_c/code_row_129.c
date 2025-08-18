#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
} Request;

typedef struct {
    const char* template;
} Environment;

typedef struct {
    const char* content;
} Response;

Response render_response_from_env(Environment env, Request request) {
    char rendered_template[1024];
    snprintf(rendered_template, sizeof(rendered_template), env.template, request.name);
    Response response = { .content = strdup(rendered_template) };
    return response;
}

Response home(Environment env) {
    Request request = { .name = "World" }; // Example name parameter
    return render_response_from_env(env, request);
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Response response = home(env);
    printf("Response: %s\n", response.content);
    free((void*)response.content); // Free the duplicated string
    return 0;
}