#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_template)(void);
    const char* (*get_name_parameter)(void);
} Environment;

const char* get_home_template(void) {
    return "Hello, %s!";
}

const char* get_user_name_from_request(void) {
    // This is a placeholder for request parsing logic
    return "World";
}

Environment create_environment() {
    Environment env;
    env.get_template = get_home_template;
    env.get_name_parameter = get_user_name_from_request;
    return env;
}

char* render_response_from_env(Environment env) {
    const char* template = env.get_template();
    const char* name = env.get_name_parameter();
    char* response = (char*)malloc(strlen(template) + strlen(name) + 1);
    if (!response) {
        exit(1); // Memory allocation failed
    }
    sprintf(response, template, name);
    return response;
}

void home() {
    Environment env = create_environment();
    char* response = render_response_from_env(env);
    printf("%s\n", response);
    free(response);
}

int main() {
    home();
    return 0;
}