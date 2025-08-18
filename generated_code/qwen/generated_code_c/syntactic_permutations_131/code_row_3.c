#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Request;

typedef struct {
    const char *template;
} Environment;

const char* get_name_parameter(const Request *request) {
    return request->name;
}

const char* get_template_from_env(Environment *env) {
    return env->template;
}

char* render_template(const char *template, const char *name) {
    char *rendered = malloc(strlen(template) + strlen(name) + 1);
    sprintf(rendered, template, name);
    return rendered;
}

const char* render_response_from_env(Environment *env, Request *request) {
    const char *name = get_name_parameter(request);
    const char *template = get_template_from_env(env);
    char *rendered = render_template(template, name);
    return rendered;
}

const char* home(Environment *env, Request *request) {
    return render_response_from_env(env, request);
}

int main() {
    Environment env = {"Hello, %s!"};
    Request request = {"Alice"};
    const char* response = home(&env, &request);
    printf("%s\n", response);
    free((void*)response);
    return 0;
}