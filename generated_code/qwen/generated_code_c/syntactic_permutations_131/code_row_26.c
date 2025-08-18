#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(void);
    char* (*get_parameter)(const char*);
} Environment;

char* get_template_example() {
    return "Hello, %s!";
}

char* get_parameter_example(const char* param_name) {
    if (strcmp(param_name, "name") == 0) {
        return "World";
    }
    return "";
}

Environment env = {get_template_example, get_parameter_example};

char* render_response_from_env(Environment* environment) {
    char* template = environment->get_template();
    char* name = environment->get_parameter("name");
    
    char* response = malloc(strlen(template) + strlen(name) + 1);
    sprintf(response, template, name);
    return response;
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