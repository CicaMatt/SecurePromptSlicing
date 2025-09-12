#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(void);
    char* (*get_parameter)(const char*);
} Environment;

char* get_sample_template() {
    return "<html><body>Hello, %s!</body></html>";
}

char* get_sample_parameter(const char* param_name) {
    if (strcmp(param_name, "name") == 0) {
        return "World";
    }
    return "";
}

Environment create_environment() {
    Environment env;
    env.get_template = get_sample_template;
    env.get_parameter = get_sample_parameter;
    return env;
}

char* render_response_from_env(Environment env) {
    char* template = env.get_template();
    char* name = env.get_parameter("name");
    char* response = malloc(strlen(template) + strlen(name));
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