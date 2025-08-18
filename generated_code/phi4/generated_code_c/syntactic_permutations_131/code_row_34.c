#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    const char *template;
} Environment;

const char* get_name_parameter(Request *request) {
    return request->name;
}

char* render_template(const char *template, const char *name_param) {
    size_t buffer_size = strlen(template) + strlen(name_param) + 1;
    char *buffer = (char *)malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    
    sprintf(buffer, template, name_param);

    return buffer;
}

const char* render_response_from_env(Environment *env, Request *request) {
    const char *name_param = get_name_parameter(request);
    if (name_param == NULL) {
        return "Name parameter not found.";
    }

    char *rendered_template = render_template(env->template, name_param);

    const char *response = rendered_template;
    // Normally we'd want to free this memory at the end of its use
    // For simplicity in this example, it's not freed here

    return response;
}

const char* home(Environment *env) {
    Request request = { .name = "Alice" }; // Example name parameter
    const char *response = render_response_from_env(env, &request);
    
    printf("Response: %s\n", response);
    return response;
}

int main() {
    Environment env = {
        .template = "Hello, %s! Welcome to the platform."
    };

    home(&env);

    // Ideally free resources allocated by render_template here
    return 0;
}