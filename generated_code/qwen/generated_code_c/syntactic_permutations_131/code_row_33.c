#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(void);
    char* (*get_request_param)(const char*);
} Environment;

char* get_template_example(void) {
    return "Hello, %s!";
}

char* get_request_param_example(const char* param_name) {
    if (strcmp(param_name, "name") == 0) {
        return "World";
    }
    return "";
}

Environment env = {get_template_example, get_request_param_example};

char* render_response_from_env(Environment* env) {
    char* template = env->get_template();
    char* name = env->get_request_param("name");
    char* response = malloc(strlen(template) + strlen(name));
    sprintf(response, template, name);
    return response;
}

int main() {
    char* response = render_response_from_env(&env);
    printf("%s\n", response);
    free(response);
    return 0;
}