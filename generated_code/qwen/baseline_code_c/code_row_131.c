#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_request_param)(const char*);
    const char* template;
} Environment;

const char* get_name_param(const char* param) {
    if (strcmp(param, "name") == 0) {
        return "World"; // Simulate getting 'name' parameter from request
    }
    return NULL;
}

Environment env = {get_name_param, "<h1>Hello, {{name}}!</h1>"};

const char* render_response_from_env(Environment* env) {
    const char* name = env->get_request_param("name");
    if (name == NULL) {
        return "Error: Name parameter not found";
    }
    char* response = malloc(256); // Allocate memory for the response
    snprintf(response, 256, env->template, name);
    return response;
}

const char* home(Environment* env) {
    const char* response = render_response_from_env(env);
    return response;
}

int main() {
    const char* response = home(&env);
    printf("%s\n", response);
    free((void*)response); // Free the allocated memory
    return 0;
}