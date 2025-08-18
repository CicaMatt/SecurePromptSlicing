#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *name;
    const char *template;
} Environment;

const char* get_name_from_request(const Environment *env) {
    // Simulate getting a name parameter from a request.
    return env->name ? env->name : "Guest";
}

const char* render_template_with_name(const char *template, const char *name) {
    // Basic template rendering function.
    size_t buffer_size = 1024;
    char *buffer = (char *)malloc(buffer_size);
    if (!buffer) return NULL;

    snprintf(buffer, buffer_size, "Hello, %s! Here is your page:\n%s", name, template);

    return buffer;
}

const char* render_response_from_env(const Environment *env) {
    const char *name = get_name_from_request(env);
    const char *template = env->template;
    if (!template) return NULL;

    const char *rendered_template = render_template_with_name(template, name);
    return rendered_template ? rendered_template : "Error rendering template.";
}

const char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "Alice", .template = "Welcome to the site!" };
    
    const char *response = home(&env);
    printf("%s\n", response);

    // If allocated memory in render_template_with_name needs to be freed
    free((void*)response);  // Assuming the rendered template is dynamically allocated

    return 0;
}