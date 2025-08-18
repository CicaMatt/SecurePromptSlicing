#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(void);
} Environment;

char* get_user_name() {
    return getenv("USER_NAME");
}

Environment create_environment() {
    Environment env;
    env.get_template = (char*(*)())malloc(sizeof(char*));
    env.get_template = &get_template_from_env;
    return env;
}

char* get_template_from_env(void) {
    return "<html><body>Hello, %s!</body></html>";
}

char* render_response_from_env(Environment env) {
    char* name = get_user_name();
    char* template = env.get_template();
    char* response = (char*)malloc(1024 * sizeof(char));
    snprintf(response, 1024, template, name);
    return response;
}

char* home(Environment env) {
    char* response = render_response_from_env(env);
    return response;
}

int main() {
    Environment env = create_environment();
    char* response = home(env);
    printf("%s\n", response);
    free(response);
    return 0;
}