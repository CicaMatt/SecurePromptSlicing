#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Environment;

char* get_name_parameter(Environment *env) {
    // Simulating getting name parameter, in real scenario it would be extracted from a request.
    return env->name ? env->name : "World";
}

const char* get_template_from_env(Environment *env) {
    // Simulating template fetching, here it's hardcoded for simplicity
    const char *template = "Hello, %s!";
    return template;
}

char* render_template(const char *template, const char *name) {
    size_t buffer_size = snprintf(NULL, 0, template, name) + 1; // Calculate required size
    char *rendered = malloc(buffer_size);
    if (rendered) {
        snprintf(rendered, buffer_size, template, name);
    }
    return rendered;
}

char* render_response_from_env(Environment *env) {
    const char *template = get_template_from_env(env);
    const char *name_param = get_name_parameter(env);

    // Render the response
    return render_template(template, name_param);
}

char* home() {
    Environment env = { .name = "User" }; // Example environment with a name

    char *response = render_response_from_env(&env);
    if (response) {
        printf("%s\n", response); // Print the response
        free(response);
    }

    return NULL;
}

int main() {
    home();
    return 0;
}