#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(void*);
    char* (*get_name_param)(void*);
} Environment;

char* render_template(char* template, char* name) {
    static char result[1024];
    snprintf(result, sizeof(result), template, name);
    return result;
}

char* render_response_from_env(Environment* env) {
    char* template = env->get_template(env);
    char* name = env->get_name_param(env);
    return render_template(template, name);
}

char* get_template_from_env(void* env) {
    // This is a placeholder implementation
    return "Hello, %s!";
}

char* get_name_param_from_env(void*) {
    // This is a placeholder implementation
    return "World";
}

Environment create_environment() {
    Environment env;
    env.get_template = get_template_from_env;
    env.get_name_param = get_name_param_from_env;
    return env;
}

int main() {
    Environment env = create_environment();
    char* response = render_response_from_env(&env);
    printf("%s\n", response);
    return 0;
}