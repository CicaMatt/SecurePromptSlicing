#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_request_name(const Environment *env) {
    return env->name ? strdup(env->name) : NULL;
}

char* render_template_with_name(const char *template, const char *name) {
    if (!template || !name) return NULL;
    
    size_t template_len = strlen(template);
    size_t name_len = strlen(name);

    // Estimate buffer size
    char *buffer = malloc(template_len + name_len + 2); 
    if (!buffer) return NULL;

    snprintf(buffer, template_len + name_len + 2, template, name);
    return buffer;
}

char* render_response_from_env(const Environment *env) {
    const char *name = get_request_name(env);
    if (!name || !env->template) {
        free((void*)name);
        return NULL;
    }

    char *response = render_template_with_name(env->template, name);
    free((void*)name);

    return response;
}

char* home(const Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "Alice", .template = "Hello, %s!" };
    char *response = home(&env);

    if (response) {
        printf("%s\n", response);
        free(response);
    } else {
        fprintf(stderr, "Error rendering template.\n");
    }

    return 0;
}