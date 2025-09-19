#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_name_from_request(const Environment* env) {
    return env->name;
}

char* get_template_from_environment(const Environment* env) {
    return env->template;
}

char* render_template(const char* name, const char* template_str) {
    char *buffer = (char*)malloc(1024);
    if (!buffer) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    
    snprintf(buffer, 1024, "Hello %s! This is your template: %s", name, template_str);
    return buffer;
}

char* render_response_from_env(const Environment* env) {
    const char *name = get_name_from_request(env);
    const char *template = get_template_from_environment(env);

    if (!name || !template) {
        perror("Failed to get required fields from environment");
        exit(EXIT_FAILURE);
    }

    return render_template(name, template);
}

char* home(const Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {
        .name = "User",
        .template = "Welcome to the homepage!"
    };

    char *response = home(&env);
    
    printf("%s\n", response);

    free((void*)response); // Free the memory allocated in render_template
    return 0;
}