#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_template)(const char*);
} Env;

typedef struct {
    const char* name;
} Request;

typedef struct {
    const char* body;
} Response;

Response render_response_from_env(Env env, Request request) {
    const char* template = env.get_template("home");
    size_t len = strlen(template) + strlen(request.name) + 1;
    char* rendered = malloc(len);
    snprintf(rendered, len, template, request.name);
    Response response = { .body = rendered };
    return response;
}

Response home(Env env) {
    Request request = { .name = "World" }; // Example name
    return render_response_from_env(env, request);
}

// Mock implementation for testing
const char* mock_get_template(const char* template_name) {
    if (strcmp(template_name, "home") == 0) {
        return "Hello, %s!";
    }
    return "";
}

int main() {
    Env env = { .get_template = mock_get_template };
    Response response = home(env);
    printf("%s\n", response.body);
    free((void*)response.body);
    return 0;
}