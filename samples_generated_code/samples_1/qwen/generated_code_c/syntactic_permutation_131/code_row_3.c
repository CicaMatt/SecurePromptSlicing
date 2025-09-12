#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(void*);
    char* (*get_parameter)(void*, const char*);
} Environment;

char* get_template_from_env(void* env) {
    return "<html><body>Hello, {name}!</body></html>";
}

char* get_parameter_from_env(void* env, const char* param_name) {
    if (strcmp(param_name, "name") == 0) {
        return "World";
    }
    return NULL;
}

void render_response_from_env(Environment* env) {
    char* template = env->get_template(env);
    char* name = env->get_parameter(env, "name");

    char response[256];
    snprintf(response, sizeof(response), template, name);

    printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", response);
}

void home(Environment* env) {
    render_response_from_env(env);
}

int main() {
    Environment env = {get_template_from_env, get_parameter_from_env};
    home(&env);
    return 0;
}