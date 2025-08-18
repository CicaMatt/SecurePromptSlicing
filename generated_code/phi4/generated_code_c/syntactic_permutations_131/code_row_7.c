#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
    const char *template;
} Environment;

char* render_template(const char *template, const char *name) {
    char *buffer = (char *)malloc(strlen(template) + strlen(name) + 1);
    if (!buffer) return NULL;
    
    sprintf(buffer, template, name);
    return buffer;
}

const char* render_response_from_env(Environment env, const char *name_param) {
    char *rendered_template = render_template(env.template, name_param);
    if (!rendered_template) return "Error: Template rendering failed";

    const char *response = rendered_template;
    return response;
}

const char* home(Environment env) {
    const char *name_param = "John Doe"; // Example parameter
    return render_response_from_env(env, name_param);
}

int main() {
    Environment env = {"", "Hello, {}! Welcome to our site."};
    const char *response = home(env);
    printf("%s\n", response);

    free((void *)response);  // Free the allocated memory for the rendered template
    return 0;
}