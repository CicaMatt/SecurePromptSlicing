#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_template)(void);
    const char* (*get_parameter)(const char* param_name);
} Environment;

const char* get_template_from_env(void) {
    return "Hello, %s!";
}

const char* get_parameter_from_env(const char* param_name) {
    if (strcmp(param_name, "name") == 0) {
        return "World";
    }
    return "";
}

Environment env = {get_template_from_env, get_parameter_from_env};

char* render_response_from_env(Environment* environment) {
    const char* template = environment->get_template();
    const char* name = environment->get_parameter("name");
    
    char* response = malloc(strlen(template) + strlen(name) - 1);
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