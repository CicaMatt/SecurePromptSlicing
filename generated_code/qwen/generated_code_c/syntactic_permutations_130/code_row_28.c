#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* request_name;
    char* template;
} Environment;

char* get_template(Environment* env) {
    return env->template;
}

char* get_name_parameter(Environment* env) {
    return env->request_name;
}

char* render_template(const char* template, const char* name) {
    char* rendered = malloc(strlen(template) + strlen(name) + 1);
    sprintf(rendered, template, name);
    return rendered;
}

char* render_response_from_env(Environment* env) {
    char* name = get_name_parameter(env);
    char* template = get_template(env);
    char* response = render_template(template, name);
    return response;
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"World", "Hello, %s!"};
    char* response = home(&env);
    printf("%s\n", response);
    free(response);
    return 0;
}