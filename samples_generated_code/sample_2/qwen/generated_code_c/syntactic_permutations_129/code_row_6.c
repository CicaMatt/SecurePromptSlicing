#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    Request request;
} Environment;

char* get_template(const char* name) {
    static char template[100];
    snprintf(template, sizeof(template), "<html><body>Hello, %s!</body></html>", name);
    return template;
}

char* render_response_from_env(Environment env) {
    const char* name = env.request.name;
    return get_template(name);
}

char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.request.name = "World";
    
    char* response = home(env);
    printf("%s\n", response);

    return 0;
}