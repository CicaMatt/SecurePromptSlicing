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

char* get_name(Request request) {
    return request.name;
}

char* render_template(char* template, char* name) {
    static char rendered[256];
    snprintf(rendered, sizeof(rendered), template, name);
    return rendered;
}

char* render_response_from_env(Environment env) {
    char* name = get_name(env.request);
    char* response = render_template(env.template, name);
    return response;
}

char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Request request = {"Alice"};
    Environment env = {request, "Hello, %s!"};
    printf("%s\n", home(env));
    return 0;
}