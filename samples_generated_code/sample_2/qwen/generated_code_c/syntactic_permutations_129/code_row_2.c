#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_name)(void);
    const char* (*get_template)(void);
} Environment;

typedef struct {
    const char* body;
} Response;

Response render_response_from_env(Environment env) {
    const char* name = env.get_name();
    const char* template = env.get_template();

    // Allocate memory for the rendered response
    size_t buffer_size = strlen(template) + strlen(name) + 1;
    char* rendered_template = (char*)malloc(buffer_size);
    if (!rendered_template) {
        exit(EXIT_FAILURE);
    }

    // Render the template with the name parameter
    snprintf(rendered_template, buffer_size, template, name);

    Response response = { .body = rendered_template };
    return response;
}

const char* get_name_from_request(void) {
    // Simulate getting a name from a request
    return "World";
}

const char* get_template_from_env(void) {
    // Simulate getting a template from the environment
    return "Hello, %s!";
}

Environment create_environment() {
    Environment env;
    env.get_name = get_name_from_request;
    env.get_template = get_template_from_env;
    return env;
}

Response home(Environment env) {
    return render_response_from_env(env);
}

int main(void) {
    Environment env = create_environment();
    Response response = home(env);

    printf("%s\n", response.body);

    // Free the allocated memory
    free((void*)response.body);

    return 0;
}