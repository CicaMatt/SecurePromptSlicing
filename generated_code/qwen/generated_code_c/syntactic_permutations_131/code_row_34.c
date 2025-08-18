#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(void*);
    void* data;
} Environment;

char* get_name_parameter(void*) {
    return "John Doe"; // Simulated name parameter from request
}

char* render_template(const char* template, const char* name) {
    static char response[1024];
    snprintf(response, sizeof(response), template, name);
    return response;
}

char* render_response_from_env(Environment* env) {
    char* name = get_name_parameter(env->data);
    char* template = env->get_template(env->data);
    return render_template(template, name);
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

char* get_template(void*) {
    return "Hello, %s!";
}

int main() {
    Environment env = {get_template, NULL};
    char* response = home(&env);
    printf("%s\n", response);
    return 0;
}