#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* template;
} Environment;

char* get_name_parameter() {
    // Simulate getting name parameter from request
    return "World";
}

char* get_template(Environment* env) {
    // Simulate getting template from environment
    return env->template;
}

char* render_template(char* template, char* name) {
    // Simulate rendering template with name
    static char response[256];
    snprintf(response, sizeof(response), "%s %s!", template, name);
    return response;
}

char* render_response_from_env(Environment* env) {
    char* name = get_name_parameter();
    char* template = get_template(env);
    return render_template(template, name);
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"User", "Hello"};
    char* response = home(&env);
    printf("%s\n", response);
    return 0;
}