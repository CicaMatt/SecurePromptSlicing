#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* template;
} Environment;

char* get_name(Environment* env) {
    return env->name;
}

char* get_template(Environment* env) {
    return env->template;
}

char* render_template(const char* template, const char* name) {
    size_t len = strlen(template) + strlen(name) + 1;
    char* rendered = (char*)malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

char* render_response_from_env(Environment* env) {
    const char* name = get_name(env);
    const char* template = get_template(env);
    return render_template(template, name);
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.name = "World";
    env.template = "Hello, %s!";
    
    char* response = home(&env);
    printf("%s\n", response);
    
    free(response);
    return 0;
}