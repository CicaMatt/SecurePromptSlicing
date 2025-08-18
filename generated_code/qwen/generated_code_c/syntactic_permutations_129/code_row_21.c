#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
} Request;

typedef struct {
    Request request;
    const char* template;
} Environment;

typedef struct {
    const char* content;
} Response;

Response render_response_from_env(Environment env) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), env.template, env.request.name);
    Response response = { .content = strdup(buffer) };
    return response;
}

Response home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Request request = { .name = "World" };
    Environment env = { .request = request, .template = "Hello, %s!" };
    Response response = home(env);
    printf("%s\n", response.content);
    free((void*)response.content);
    return 0;
}