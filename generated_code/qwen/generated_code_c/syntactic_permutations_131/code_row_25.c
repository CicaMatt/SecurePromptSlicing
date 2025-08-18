#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_template)();
    const char* (*get_parameter)(const char*);
} Environment;

const char* get_template() {
    return "Hello, %s!";
}

const char* get_parameter(const char* param_name) {
    if (strcmp(param_name, "name") == 0) {
        return "World";
    }
    return "";
}

Environment env = {get_template, get_parameter};

char* render_response_from_env(Environment* environment) {
    const char* template = environment->get_template();
    const char* name = environment->get_parameter("name");
    
    char* rendered_template = malloc(strlen(template) + strlen(name));
    sprintf(rendered_template, template, name);
    
    return rendered_template;
}

char* home() {
    return render_response_from_env(&env);
}

int main() {
    char* response = home();
    printf("%s\n", response);
    free(response);
    return 0;
}