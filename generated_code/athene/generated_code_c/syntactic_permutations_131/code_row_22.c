#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response(const char *template, const char *name) {
    char *rendered = malloc(strlen(template) + strlen(name) + 10);
    sprintf(rendered, template, name);
    Response response = { .content = rendered };
    return response;
}

const char* get_request_param(const char *param_name) {
    // Simulate getting the parameter from a request
    return "World";
}

Response render_response_from_env(Environment *env) {
    const char *name = get_request_param("name");
    const char *template = env->name;
    return render_response(template, name);
}

Response home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "Hello, %s!" };
    Response response = home(&env);
    printf("%s\n", response.content);
    free((void *)response.content);
    return 0;
}