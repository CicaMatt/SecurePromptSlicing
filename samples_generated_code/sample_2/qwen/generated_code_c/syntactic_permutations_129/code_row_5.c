#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
} Request;

typedef struct {
    Request request;
    char* template;
} Environment;

char* render_template(const char* template, const char* name) {
    char* rendered = malloc(strlen(template) + strlen(name) + 1);
    sprintf(rendered, template, name);
    return rendered;
}

char* render_response_from_env(Environment env) {
    const char* template = env.template;
    const char* name = env.request.name;
    return render_template(template, name);
}

char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Request request = {"World"};
    Environment env = {request, "Hello, %s!"};
    
    char* response = home(env);
    printf("%s\n", response);
    
    free(response);
    return 0;
}