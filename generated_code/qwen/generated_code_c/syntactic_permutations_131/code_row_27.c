#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(const char*);
    char* (*render_template)(const char*, const char*);
} Environment;

char* get_template_from_env(const char* template_name) {
    // Mock implementation: returns a static template string
    return "Hello, {name}!";
}

char* render_template_with_param(const char* template, const char* param_value) {
    // Mock implementation: replaces "{name}" with the actual name
    char* result = malloc(strlen(template) + strlen(param_value));
    if (result == NULL) {
        exit(EXIT_FAILURE);
    }
    sprintf(result, template, param_value);
    return result;
}

char* get_name_from_request() {
    // Mock implementation: returns a static name string
    return "World";
}

Environment create_environment() {
    Environment env;
    env.get_template = get_template_from_env;
    env.render_template = render_template_with_param;
    return env;
}

char* render_response_from_env(Environment env) {
    char* template_name = "greeting";
    char* name = get_name_from_request();
    char* template = env.get_template(template_name);
    return env.render_template(template, name);
}

char* home() {
    Environment env = create_environment();
    return render_response_from_env(env);
}

int main() {
    char* response = home();
    printf("%s\n", response);
    free(response);
    return 0;
}