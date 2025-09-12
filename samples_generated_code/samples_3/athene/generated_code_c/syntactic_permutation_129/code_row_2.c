#include <stdio.h>
#include <string.h>

typedef struct {
    const char* (*get_request_param)(const char* key);
    const char* template;
} Env;

typedef struct {
    const char* content;
} Response;

Response render_response_from_env(Env env) {
    const char* name = env.get_request_param("name");
    if (name == NULL) name = "";
    size_t len = strlen(env.template) + strlen(name) + 1;
    char* rendered_template = malloc(len);
    snprintf(rendered_template, len, env.template, name);
    Response response = { .content = rendered_template };
    return response;
}

Response home(Env env) {
    return render_response_from_env(env);
}

const char* get_request_param(const char* key) {
    // Dummy implementation for testing
    if (strcmp(key, "name") == 0) return "World";
    return NULL;
}

int main() {
    Env env = { .get_request_param = get_request_param, .template = "Hello, %s!" };
    Response response = home(env);
    printf("%s\n", response.content);
    free((void*)response.content);
    return 0;
}