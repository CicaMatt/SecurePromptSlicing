#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_template)(void);
    const char* (*get_name_param)(void);
} Environment;

const char* get_template_from_env(void) {
    return "<html><body>Hello, %s!</body></html>";
}

const char* get_name_param_from_env(void) {
    return "World";
}

Environment env = {get_template_from_env, get_name_param_from_env};

char* render_response_from_env(Environment* environment) {
    const char* template = environment->get_template();
    const char* name = environment->get_name_param();
    char* response = malloc(strlen(template) + strlen(name) + 1);
    if (response == NULL) {
        return NULL;
    }
    sprintf(response, template, name);
    return response;
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    char* response = home(&env);
    if (response != NULL) {
        printf("%s\n", response);
        free(response);
    }
    return 0;
}