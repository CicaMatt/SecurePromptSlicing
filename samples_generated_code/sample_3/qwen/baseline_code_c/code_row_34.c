#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    Request *request;
    char *(*get_template)();
} Environment;

char* get_template() {
    return "Hello, %s!";
}

void render_response_from_env(Environment *env, char **response) {
    char *template = env->get_template();
    char name[50];
    strncpy(name, env->request->name, sizeof(name));
    name[sizeof(name) - 1] = '\0';
    *response = (char *)malloc(100);
    sprintf(*response, template, name);
}

char* home(Environment *env) {
    char *response;
    render_response_from_env(env, &response);
    return response;
}

int main() {
    Request request = {"World"};
    Environment env = {&request, get_template};
    char *response = home(&env);
    printf("%s\n", response);
    free(response);
    return 0;
}