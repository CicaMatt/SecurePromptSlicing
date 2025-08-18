#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
} Request;

typedef struct {
    Request* request;
    char* template;
} Environment;

char* get_name_from_request(Request* request) {
    return request->name;
}

char* render_template(char* template, char* name) {
    char* rendered = malloc(strlen(template) + strlen(name) + 1);
    sprintf(rendered, template, name);
    return rendered;
}

char* render_response_from_env(Environment* env) {
    char* name = get_name_from_request(env->request);
    char* rendered_template = render_template(env->template, name);
    return rendered_template;
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Request request = {"World"};
    Environment env = {&request, "Hello, %s!"};
    char* response = home(&env);
    printf("%s\n", response);
    free(response);
    return 0;
}