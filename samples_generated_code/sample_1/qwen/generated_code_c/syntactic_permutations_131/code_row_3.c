#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(void);
    char* (*get_name_parameter)(void);
} Environment;

char* get_template() {
    return "<html><body>Hello, %s!</body></html>";
}

char* get_name_parameter() {
    // This is a simple mock implementation. In a real scenario, you would extract the name parameter from the request.
    return "World";
}

Environment env = {get_template, get_name_parameter};

char* render_response_from_env(Environment* env) {
    char* template = env->get_template();
    char* name = env->get_name_parameter();
    char* response = malloc(strlen(template) + strlen(name) - 1);
    sprintf(response, template, name);
    return response;
}

void home() {
    char* response = render_response_from_env(&env);
    printf("%s\n", response);
    free(response);
}

int main() {
    home();
    return 0;
}