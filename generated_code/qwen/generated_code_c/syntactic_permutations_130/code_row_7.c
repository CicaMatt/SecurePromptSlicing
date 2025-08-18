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
    char* content;
} Response;

Response render_template(const char* template, const char* name) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), template, name);
    Response response = {strdup(buffer)};
    return response;
}

void free_response(Response response) {
    free(response.content);
}

Response render_response_from_env(Environment env, Request request) {
    const char* template = env.template;
    const char* name = request.name;
    return render_template(template, name);
}

Response home(Environment env) {
    Request request = {"World"};
    return render_response_from_env(env, request);
}

int main() {
    Environment env = {"Hello, %s!"};
    Response response = home(env);
    printf("%s\n", response.content);
    free_response(response);
    return 0;
}