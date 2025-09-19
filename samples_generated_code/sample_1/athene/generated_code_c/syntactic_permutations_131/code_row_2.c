#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_template)(const char*);
} Environment;

typedef struct {
    const char* name;
} Request;

typedef struct {
    const char* content;
} Response;

Response render_response_from_env(Environment env, Request request) {
    const char* template = env.get_template("home");
    size_t len = strlen(template) + strlen(request.name) + 100;
    char* rendered = malloc(len);
    snprintf(rendered, len, template, request.name);
    Response response = {.content = rendered};
    return response;
}

Response home(Environment env) {
    Request request = { .name = "World" };
    return render_response_from_env(env, request);
}

const char* get_home_template(const char* name) {
    return "Hello, %s!";
}

int main() {
    Environment env = { .get_template = get_home_template };
    Response response = home(env);
    printf("%s\n", response.content);
    free((void*)response.content);
    return 0;
}