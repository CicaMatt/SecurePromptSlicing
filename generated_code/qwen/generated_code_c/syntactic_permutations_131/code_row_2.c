#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(void);
    char* (*get_name_parameter)(void);
} Environment;

char* get_template() {
    return "<html><body><h1>Hello, %s!</h1></body></html>";
}

char* get_name_parameter() {
    return "World";
}

Environment* create_environment() {
    Environment* env = (Environment*)malloc(sizeof(Environment));
    if (!env) return NULL;
    env->get_template = get_template;
    env->get_name_parameter = get_name_parameter;
    return env;
}

void destroy_environment(Environment* env) {
    free(env);
}

char* render_response_from_env(Environment* env) {
    char* template = env->get_template();
    char* name = env->get_name_parameter();
    char* response = (char*)malloc(strlen(template) + strlen(name) - 1); // -1 for %s
    if (!response) return NULL;
    sprintf(response, template, name);
    return response;
}

char* home(Environment* env) {
    char* response = render_response_from_env(env);
    return response;
}

int main() {
    Environment* env = create_environment();
    if (!env) {
        fprintf(stderr, "Failed to create environment\n");
        return EXIT_FAILURE;
    }

    char* response = home(env);
    if (response) {
        printf("%s\n", response);
        free(response);
    } else {
        fprintf(stderr, "Failed to render response\n");
    }

    destroy_environment(env);
    return EXIT_SUCCESS;
}