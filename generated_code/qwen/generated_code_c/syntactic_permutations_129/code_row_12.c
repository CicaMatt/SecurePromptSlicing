#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(void*);
    char* (*render_template)(void*, const char*, const char*);
} Environment;

char* get_name(void) {
    return "World";
}

char* get_template(void* env) {
    return "Hello, %s!";
}

char* render_template(void* env, const char* template, const char* name) {
    char* result = malloc(100);
    sprintf(result, template, name);
    return result;
}

void* create_env() {
    Environment* env = malloc(sizeof(Environment));
    env->get_template = get_template;
    env->render_template = render_template;
    return env;
}

char* render_response_from_env(void* env) {
    char* name = get_name();
    char* template = ((Environment*)env)->get_template(env);
    return ((Environment*)env)->render_template(env, template, name);
}

char* home(void* env) {
    return render_response_from_env(env);
}

int main() {
    void* env = create_env();
    char* response = home(env);
    printf("%s\n", response);
    free(response);
    free(env);
    return 0;
}