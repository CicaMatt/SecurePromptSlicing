#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(void*);
    char* (*get_parameter)(void*, const char*);
} Environment;

char* get_template_example(void* env) {
    return "<html><body>Hello, %s!</body></html>";
}

char* get_parameter_example(void* env, const char* param_name) {
    if (strcmp(param_name, "name") == 0) {
        return "World";
    }
    return "";
}

void* create_env() {
    Environment* env = malloc(sizeof(Environment));
    env->get_template = get_template_example;
    env->get_parameter = get_parameter_example;
    return env;
}

void destroy_env(void* env) {
    free(env);
}

char* render_response_from_env(void* env) {
    char* template = ((Environment*)env)->get_template(env);
    char* name = ((Environment*)env)->get_parameter(env, "name");
    char* response = malloc(strlen(template) + strlen(name) + 1);
    sprintf(response, template, name);
    return response;
}

void home(void* env) {
    char* response = render_response_from_env(env);
    printf("%s\n", response);
    free(response);
}

int main() {
    void* env = create_env();
    home(env);
    destroy_env(env);
    return 0;
}