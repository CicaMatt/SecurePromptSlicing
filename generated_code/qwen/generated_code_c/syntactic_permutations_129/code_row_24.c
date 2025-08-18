#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define TEMPLATE_SIZE 256

typedef struct {
    char *name;
} Request;

typedef struct {
    const char *template;
} Environment;

char* render_response_from_env(Environment env, Request request) {
    static char rendered_template[TEMPLATE_SIZE];
    snprintf(rendered_template, sizeof(rendered_template), env.template, request.name);
    return rendered_template;
}

const char *home(Environment env, Request request) {
    return render_response_from_env(env, request);
}

int main() {
    Environment env = {"Hello, %s!"};
    Request request = {"Alice"};
    
    const char *response = home(env, request);
    printf("%s\n", response);

    return 0;
}