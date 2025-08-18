#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_parameter)(const char*);
    const char* (*get_template)();
} Environment;

const char* get_name_parameter(const char* param) {
    if (strcmp(param, "name") == 0) {
        return "World"; // Example name
    }
    return NULL;
}

const char* get_home_template() {
    return "Hello, %s!";
}

Environment create_environment() {
    Environment env;
    env.get_parameter = get_name_parameter;
    env.get_template = get_home_template;
    return env;
}

const char* render_response_from_env(Environment env) {
    const char* name = env.get_parameter("name");
    if (!name) {
        return "Hello, Guest!";
    }
    const char* template = env.get_template();
    size_t len = strlen(template) + strlen(name);
    char* response = (char*)malloc(len + 1);
    sprintf(response, template, name);
    return response;
}

const char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = create_environment();
    const char* response = home(env);
    printf("%s\n", response);
    free((void*)response); // Free the allocated memory
    return 0;
}