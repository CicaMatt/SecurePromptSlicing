#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESPONSE_BUFFER_SIZE 1024

typedef struct {
    char *name;
    const char *template;
} Environment;

char* render_template(const char *template, const char *name) {
    static char response[RESPONSE_BUFFER_SIZE];
    snprintf(response, sizeof(response), template, name);
    return response;
}

const char* render_response_from_env(Environment env) {
    const char *response = render_template(env.template, env.name);
    return response;
}

const char* home() {
    Environment env;
    env.name = getenv("NAME");
    if (!env.name) {
        env.name = "Guest";
    }
    env.template = "<h1>Hello, %s!</h1>";
    
    return render_response_from_env(env);
}

int main() {
    printf("%s\n", home());
    return 0;
}