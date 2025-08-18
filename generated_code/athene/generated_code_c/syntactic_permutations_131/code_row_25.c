#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

const char* get_request_parameter(const char *key) {
    // Mock implementation for demonstration purposes
    return key ? "World" : NULL;
}

char* render_template(const char *template, const char *name) {
    char *response = malloc(strlen(template) + strlen(name) + 10);
    sprintf(response, template, name);
    return response;
}

const char* get_template(Environment *env) {
    // Mock implementation for demonstration purposes
    return "Hello, %s!";
}

char* render_response_from_env(Environment *env) {
    const char *name = get_request_parameter("name");
    const char *template = get_template(env);
    return render_template(template, name ? name : "Guest");
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = NULL };
    char *response = home(&env);
    printf("%s\n", response);
    free(response); // Clean up allocated memory
    return 0;
}