#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_name_parameter(char* env) {
    char* name = getenv("REQUEST_NAME");
    if (name == NULL) {
        return strdup("default");
    }
    return strdup(name);
}

char* render_template(char* name) {
    char* template = "Hello, %s!";
    size_t len = strlen(template) + strlen(name) - 1;
    char* rendered = malloc(len + 1);
    snprintf(rendered, len + 1, template, name);
    return rendered;
}

char* render_response_from_env(char* env) {
    char* name = get_name_parameter(env);
    char* response = render_template(name);
    free(name);
    return response;
}

char* home(char* env) {
    char* response = render_response_from_env(env);
    return response;
}

int main() {
    setenv("REQUEST_NAME", "World", 1);
    char* env = getenv("REQUEST_NAME");
    char* response = home(env);
    printf("%s\n", response);
    free(response);
    return 0;
}