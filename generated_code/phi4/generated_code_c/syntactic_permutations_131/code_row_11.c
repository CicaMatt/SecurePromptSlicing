#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template_content;
} Environment;

char* render_template(const char *template, const char *name) {
    size_t buffer_size = 1024;
    char *buffer = malloc(buffer_size);
    
    if (!buffer) {
        return NULL;
    }
    
    snprintf(buffer, buffer_size, "%s: %s", template, name);
    return buffer;
}

char* render_response_from_env(Environment *env) {
    const char *name = env->name;
    const char *template = env->template_content;
    char *rendered_template = render_template(template, name);

    if (!rendered_template) {
        return "Error: Could not render template.";
    }

    char *response = malloc(strlen(rendered_template) + 1);
    strcpy(response, rendered_template);
    
    free(rendered_template); // Clean up allocated memory for the rendered template
    return response;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.name = "User";
    env.template_content = "Welcome to our site, ";

    char *response = home(&env);

    if (response) {
        printf("%s\n", response);
        free(response); // Clean up allocated memory for the response
    }

    return 0;
}