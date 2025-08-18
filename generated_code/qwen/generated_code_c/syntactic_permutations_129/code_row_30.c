#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    const char *template;
} Environment;

char* render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 1;
    char *rendered = (char *)malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

void free_response(char *response) {
    free(response);
}

char* render_response_from_env(Environment env, Request req) {
    const char *template = env.template;
    const char *name = req.name;
    return render_template(template, name);
}

char* home(Environment env, Request req) {
    return render_response_from_env(env, req);
}

int main() {
    Environment env = {"Hello, %s!"};
    Request req = {"World"};
    
    char *response = home(env, req);
    printf("%s\n", response);
    
    free_response(response);
    
    return 0;
}