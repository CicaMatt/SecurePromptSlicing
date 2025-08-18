#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
} Request;

typedef struct {
    Request request;
} Environment;

char* get_template(const char* name) {
    static char template[256];
    snprintf(template, sizeof(template), "<html><body><h1>Hello, %s!</h1></body></html>", name);
    return template;
}

char* render_response_from_env(Environment* env) {
    char* name = env->request.name;
    char* rendered_template = get_template(name);
    return strdup(rendered_template);
}

char* home(Environment* env) {
    char* response = render_response_from_env(env);
    return response;
}

int main() {
    Environment env;
    strcpy(env.request.name, "World");

    char* response = home(&env);
    printf("%s\n", response);

    free(response);
    return 0;
}