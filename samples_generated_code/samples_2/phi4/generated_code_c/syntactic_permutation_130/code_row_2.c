#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* (*get_template)(void*);
    char* name;
} Environment;

char* get_template(void *env) {
    return "Hello, %s!";
}

char* render_response_from_env(Environment *env) {
    const char *template = env->get_template(env);
    if (!template) return NULL;

    char *response = malloc(50);
    snprintf(response, 50, template, env->name);
    return response;
}

char* home(void *env) {
    Environment e = { .get_template = get_template };
    e.name = "World";
    
    char *response = render_response_from_env(&e);
    if (!response) return NULL;

    printf("%s\n", response);
    free(response);
    return response;
}

int main() {
    home(NULL);
    return 0;
}