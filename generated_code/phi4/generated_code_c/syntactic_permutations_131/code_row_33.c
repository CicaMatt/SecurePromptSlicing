#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[256];
} Request;

typedef struct {
    const char *template;
} Environment;

Environment env = { .template = "Hello, %s!" };

char* render_template(const char* template_str, const char* name) {
    size_t buffer_size = snprintf(NULL, 0, template_str, name) + 1; // Calculate required buffer size
    char *buffer = malloc(buffer_size);
    if (buffer != NULL) {
        snprintf(buffer, buffer_size, template_str, name); // Format the string
    }
    return buffer;
}

char* render_response_from_env(const Environment *env, const Request *request) {
    return render_template(env->template, request->name);
}

void home() {
    Request request = { .name = "World" };
    char *response = render_response_from_env(&env, &request);

    if (response != NULL) {
        printf("%s\n", response);
        free(response); // Free allocated memory
    } else {
        fprintf(stderr, "Failed to render response.\n");
    }
}

int main() {
    home();
    return 0;
}