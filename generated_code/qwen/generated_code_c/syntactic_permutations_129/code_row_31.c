#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_parameter)(const char*);
    const char* (*get_template)();
} Environment;

const char* get_name_parameter(const char* param) {
    if (strcmp(param, "name") == 0) {
        return "John Doe";
    }
    return NULL;
}

const char* get_template() {
    return "Hello, %s!";
}

Environment env = {get_name_parameter, get_template};

char* render_response_from_env(Environment* environment) {
    const char* name = environment->get_parameter("name");
    const char* template = environment->get_template();
    
    if (name == NULL || template == NULL) {
        return strdup("Error rendering response");
    }
    
    size_t len = snprintf(NULL, 0, template, name);
    char* response = malloc(len + 1);
    if (response != NULL) {
        snprintf(response, len + 1, template, name);
    }
    return response;
}

void home(Environment* env) {
    char* response = render_response_from_env(env);
    printf("%s\n", response);
    free(response);
}

int main() {
    home(&env);
    return 0;
}