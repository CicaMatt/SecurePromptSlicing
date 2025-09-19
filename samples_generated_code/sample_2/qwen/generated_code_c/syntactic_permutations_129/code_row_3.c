#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_parameter)(const char* param_name);
    char* (*get_template)();
} Environment;

char* get_name_parameter(const char* param_name) {
    if (strcmp(param_name, "name") == 0) {
        return "World";
    }
    return NULL;
}

char* get_home_template() {
    return "<html><body>Hello, %s!</body></html>";
}

Environment create_environment() {
    Environment env;
    env.get_parameter = get_name_parameter;
    env.get_template = get_home_template;
    return env;
}

char* render_response_from_env(Environment env) {
    char* name = env.get_parameter("name");
    char* template = env.get_template();
    char* response = malloc(1024);
    sprintf(response, template, name);
    return response;
}

char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = create_environment();
    char* response = home(env);
    printf("%s\n", response);
    free(response);
    return 0;
}