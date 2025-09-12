#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* template;
} Environment;

char* render_template(const char* template, const char* name) {
    char* result = (char*)malloc(strlen(template) + strlen(name) + 1);
    sprintf(result, template, name);
    return result;
}

char* render_response_from_env(Environment env) {
    char* rendered_template = render_template(env.template, env.name);
    return rendered_template;
}

char* home(Environment env) {
    char* response = render_response_from_env(env);
    return response;
}

int main() {
    Environment env;
    env.name = "World";
    env.template = "Hello, %s!";

    char* response = home(env);
    printf("%s\n", response);

    free(response);
    return 0;
}