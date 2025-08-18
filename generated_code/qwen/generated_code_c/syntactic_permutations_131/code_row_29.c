#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_template)(void);
    const char* (*get_request_parameter)(const char*);
} Environment;

const char* get_user_template(void) {
    return "Hello, %s!";
}

const char* get_name_from_request(const char* param_name) {
    if (strcmp(param_name, "name") == 0) {
        return "World";
    }
    return "";
}

Environment env = {get_user_template, get_name_from_request};

char* render_response_from_env(Environment environment) {
    const char* template = environment.get_template();
    const char* name = environment.get_request_parameter("name");
    char* response = malloc(strlen(template) + strlen(name));
    sprintf(response, template, name);
    return response;
}

const char* home(Environment environment) {
    return render_response_from_env(environment);
}

int main() {
    const char* response = home(env);
    printf("%s\n", response);
    free((void*)response);
    return 0;
}