#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_parameter)(const char*);
    const char* template;
} Environment;

const char* get_name_parameter(const char* param) {
    if (strcmp(param, "name") == 0) {
        return "World";
    }
    return NULL;
}

Environment env = {get_name_parameter, "Hello, %s!"};

char* render_template(const char* template, const char* name) {
    size_t len = snprintf(NULL, 0, template, name);
    char* rendered = (char*)malloc(len + 1);
    if (!rendered) return NULL;
    snprintf(rendered, len + 1, template, name);
    return rendered;
}

const char* render_response_from_env(Environment* env) {
    const char* name = env->get_parameter("name");
    if (!name) return "No name parameter found";
    char* response = render_template(env->template, name);
    return response;
}

const char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    const char* response = home(&env);
    printf("%s\n", response);
    free((void*)response);
    return 0;
}