#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
} Request;

typedef struct {
    char* template;
} Environment;

typedef struct {
    char* content;
} Response;

Response render_template(const char* template, const char* name) {
    char* content = malloc(strlen(template) + strlen(name) + 1);
    sprintf(content, template, name);
    Response response = { .content = content };
    return response;
}

Response render_response_from_env(Environment env, Request request) {
    const char* template = env.template;
    const char* name = request.name;
    return render_template(template, name);
}

Response home(Environment env) {
    Request request = { .name = "World" }; // Example name parameter
    return render_response_from_env(env, request);
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Response response = home(env);
    printf("%s\n", response.content);
    free(response.content);
    return 0;
}