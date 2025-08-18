#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    Request *request;
    char *template;
} Environment;

char* get_name_parameter(Request *request) {
    return request->name;
}

char* render_template(Environment *env, const char *name) {
    char *rendered = malloc(strlen(env->template) + strlen(name) + 1);
    sprintf(rendered, env->template, name);
    return rendered;
}

char* render_response_from_env(Environment *env) {
    const char *name = get_name_parameter(env->request);
    char *rendered_template = render_template(env, name);
    return rendered_template;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Request request = {"World"};
    Environment env = {&request, "Hello, %s!"};

    char *response = home(&env);
    printf("%s\n", response);

    free(response);
    return 0;
}