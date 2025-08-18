#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_parameter)(const char*);
    char* (*get_template)();
} Environment;

char* get_name_parameter(const char* param) {
    if (strcmp(param, "name") == 0) {
        return "John Doe"; // Example name
    }
    return NULL;
}

char* get_example_template() {
    return "<html><body><h1>Hello, %s!</h1></body></html>";
}

Environment env = {get_name_parameter, get_example_template};

char* render_response_from_env(Environment* env) {
    char* template = env->get_template();
    char* name = env->get_parameter("name");
    if (template && name) {
        char* response = malloc(strlen(template) + strlen(name) - 1);
        sprintf(response, template, name);
        return response;
    }
    return NULL;
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    char* response = home(&env);
    if (response) {
        printf("%s\n", response);
        free(response);
    }
    return 0;
}