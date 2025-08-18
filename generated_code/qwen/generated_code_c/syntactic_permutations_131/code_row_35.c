#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(void*);
    char* (*get_name_param)(void*);
} Environment;

char* render_template(const char* template, const char* name) {
    char* result = malloc(strlen(template) + strlen(name) + 1);
    sprintf(result, template, name);
    return result;
}

char* render_response_from_env(Environment* env) {
    char* name_param = env->get_name_param(env);
    char* template = env->get_template(env);
    char* rendered_template = render_template(template, name_param);
    free(name_param);
    return rendered_template;
}

char* get_template(void* env) {
    // This should be replaced with actual template retrieval logic
    return "Hello, %s!";
}

char* get_name_param(void* env) {
    // This should be replaced with actual parameter retrieval logic
    return strdup("World");
}

typedef struct {
    Environment base;
} HomeEnv;

int main() {
    HomeEnv home_env = {{get_template, get_name_param}};
    char* response = render_response_from_env((Environment*)&home_env);
    printf("%s\n", response);
    free(response);
    return 0;
}