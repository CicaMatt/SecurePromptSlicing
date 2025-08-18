#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_name_parameter(Environment *env) {
    // Simulate getting a name parameter from user request
    return env->name ? env->name : "Guest";
}

char* get_template_from_env(Environment *env) {
    // Get the template string from environment
    return env->template;
}

char* render_template_with_name(char *template, char *name) {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), template, name);
    return buffer;
}

char* render_response_from_env(Environment *env) {
    char *name = get_name_parameter(env);
    char *template = get_template_from_env(env);
    char *response = render_template_with_name(template, name);
    return response;
}

char* home() {
    Environment env = { .name = "Alice", .template = "Hello, %s!" };
    return render_response_from_env(&env);
}

int main() {
    char *response = home();
    printf("%s\n", response);
    return 0;
}