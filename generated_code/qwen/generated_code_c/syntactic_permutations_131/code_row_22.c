#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_parameter)(const char*);
    const char* template;
} Environment;

const char* get_name(const char* parameter) {
    if (strcmp(parameter, "name") == 0) {
        return "World";
    }
    return "";
}

Environment create_environment() {
    Environment env;
    env.get_parameter = get_name;
    env.template = "Hello, %s!";
    return env;
}

const char* render_response_from_env(Environment* env) {
    const char* name = env->get_parameter("name");
    static char response[100];
    snprintf(response, sizeof(response), env->template, name);
    return response;
}

const char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = create_environment();
    printf("%s\n", home(&env));
    return 0;
}