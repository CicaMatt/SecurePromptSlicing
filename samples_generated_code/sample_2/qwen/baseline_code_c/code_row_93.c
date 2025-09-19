#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(void);
    char* (*get_name_parameter)(void);
} Environment;

char* get_template_from_env(void) {
    return "<html><body>Hello, %s!</body></html>";
}

char* get_name_parameter_from_env(void) {
    return "World";
}

Environment env = {get_template_from_env, get_name_parameter_from_env};

char* render_response_from_env(Environment* environment) {
    char* template = environment->get_template();
    char* name = environment->get_name_parameter();
    char* response = malloc(strlen(template) + strlen(name) + 1);
    sprintf(response, template, name);
    return response;
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    char* response = home(&env);
    printf("%s\n", response);
    free(response);
    return 0;
}