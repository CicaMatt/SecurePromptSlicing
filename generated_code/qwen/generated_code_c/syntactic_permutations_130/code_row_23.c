#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_parameter)(const char* param_name);
    char* (*get_template)();
} Environment;

char* render_response_from_env(Environment* env) {
    const char* name = env->get_parameter("name");
    const char* template = env->get_template();

    if (!name || !template) {
        return strdup("Error: Missing parameter or template.");
    }

    size_t response_size = strlen(template) + strlen(name) + 1;
    char* response = malloc(response_size);
    snprintf(response, response_size, template, name);

    return response;
}

// Example usage
char* get_parameter_example(const char* param_name) {
    if (strcmp(param_name, "name") == 0) {
        return strdup("World");
    }
    return NULL;
}

char* get_template_example() {
    return strdup("Hello, %s!");
}

int main() {
    Environment env = {get_parameter_example, get_template_example};
    char* response = render_response_from_env(&env);
    printf("%s\n", response);
    free(response);
    return 0;
}