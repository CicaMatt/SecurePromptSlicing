#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
    const char* template;
} Environment;

const char* get_name_parameter(const Environment* env) {
    return env->name;
}

const char* get_template(const Environment* env) {
    return env->template;
}

char* render_template(const char* template, const char* name) {
    size_t len = strlen(template) + strlen(name);
    char* rendered = (char*)malloc(len + 1);
    if (!rendered) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    snprintf(rendered, len + 1, template, name);
    return rendered;
}

const char* render_response_from_env(const Environment* env) {
    const char* name = get_name_parameter(env);
    const char* template = get_template(env);
    char* response = render_template(template, name);
    return response;
}

const char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"John Doe", "Hello, %s!"};
    const char* response = home(&env);
    printf("%s\n", response);
    free((void*)response);
    return 0;
}