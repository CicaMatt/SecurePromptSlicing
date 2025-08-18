#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_request_name(Environment env) {
    return env.name ? env.name : "Guest";
}

char* render_template(char *template, const char *name) {
    if (template == NULL || name == NULL) return strdup("Invalid template or name.");
    
    size_t needed = snprintf(NULL, 0, "%s", template) + strlen(name) + 1;
    char *buffer = malloc(needed);
    snprintf(buffer, needed, template, name);
    return buffer;
}

char* render_response_from_env(Environment env) {
    const char *name = get_request_name(env);
    char *rendered_template = render_template(env.template, name);
    return rendered_template;
}

char* home() {
    Environment env = { .name = "Alice", .template = "Hello, %s! Welcome to our site." };
    return render_response_from_env(env);
}

int main() {
    char *response = home();
    printf("%s\n", response);
    free(response);
    return 0;
}