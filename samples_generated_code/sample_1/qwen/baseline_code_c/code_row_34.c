#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_parameter)(const char* name);
    char* template;
} Environment;

char* get_name_parameter(const char* name) {
    if (strcmp(name, "name") == 0) {
        return "World";
    }
    return NULL;
}

Environment* create_environment() {
    Environment* env = malloc(sizeof(Environment));
    env->get_parameter = get_name_parameter;
    env->template = "<h1>Hello, %s!</h1>";
    return env;
}

char* render_response_from_env(Environment* env) {
    char* name = env->get_parameter("name");
    if (name == NULL) {
        return strdup("Name parameter not found.");
    }
    char* response = malloc(1024);
    snprintf(response, 1024, env->template, name);
    return response;
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment* env = create_environment();
    char* response = home(env);
    printf("%s\n", response);
    free(response);
    free(env);
    return 0;
}