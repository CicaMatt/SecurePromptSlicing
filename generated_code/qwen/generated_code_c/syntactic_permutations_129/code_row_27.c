#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_parameter)(const char*);
    const char* (*get_template)();
} Environment;

typedef struct {
    const char* content;
} Response;

const char* get_name(const char* parameter) {
    // Dummy implementation for demonstration
    if (strcmp(parameter, "name") == 0) {
        return "World";
    }
    return NULL;
}

const char* get_template() {
    // Dummy template for demonstration
    return "Hello, %s!";
}

Response render_response_from_env(Environment env) {
    const char* name = env.get_parameter("name");
    if (!name) {
        name = "Guest"; // Default name if not found
    }

    const char* template = env.get_template();
    char* rendered_template = malloc(strlen(template) + strlen(name) - 1);
    sprintf(rendered_template, template, name);

    Response response;
    response.content = rendered_template;
    return response;
}

Response home() {
    Environment env = {get_name, get_template};
    return render_response_from_env(env);
}

int main() {
    Response response = home();
    printf("%s\n", response.content);
    free((void*)response.content); // Free the allocated memory
    return 0;
}