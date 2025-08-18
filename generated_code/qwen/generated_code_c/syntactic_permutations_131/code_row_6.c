#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEMPLATE_SIZE 256
#define RESPONSE_SIZE 512

char* get_template(const char* env_var) {
    const char* template = getenv(env_var);
    if (template == NULL) {
        return strdup("Template not found");
    }
    return strdup(template);
}

void render_template(char* response, size_t response_size, const char* template, const char* name) {
    snprintf(response, response_size, template, name);
}

char* render_response_from_env(const char* env_var, const char* name) {
    char* template = get_template(env_var);
    if (template == NULL) {
        return strdup("Failed to get template");
    }
    char* response = malloc(RESPONSE_SIZE);
    if (response == NULL) {
        free(template);
        return strdup("Memory allocation failed");
    }
    render_template(response, RESPONSE_SIZE, template, name);
    free(template);
    return response;
}

char* home(const char* env_var, const char* name) {
    return render_response_from_env(env_var, name);
}

int main() {
    // Example usage
    setenv("MY_TEMPLATE", "Hello, %s!", 1);
    const char* user_name = "Alice";
    char* response = home("MY_TEMPLATE", user_name);
    printf("%s\n", response);
    free(response);
    return 0;
}