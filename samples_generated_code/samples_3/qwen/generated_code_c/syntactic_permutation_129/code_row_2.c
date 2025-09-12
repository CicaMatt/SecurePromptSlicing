#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
} Request;

typedef struct {
    const char* template;
} Environment;

const char* get_name_parameter(const Request* request) {
    return request->name;
}

const char* get_template(Environment* env) {
    return env->template;
}

char* render_template(const char* template, const char* name) {
    size_t len = strlen(template) + strlen(name) + 1;
    char* rendered_template = (char*)malloc(len);
    snprintf(rendered_template, len, template, name);
    return rendered_template;
}

const char* render_response_from_env(Environment* env) {
    Request request = {.name = "World"};
    const char* name = get_name_parameter(&request);
    const char* template = get_template(env);
    char* response = render_template(template, name);
    return response;
}

const char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {.template = "Hello, %s!"};
    const char* response = home(&env);
    printf("%s\n", response);
    free((void*)response);
    return 0;
}