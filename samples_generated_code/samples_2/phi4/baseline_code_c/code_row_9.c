#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

const char* get_name(const Environment *env) {
    return env->name ? env->name : "Guest";
}

const char* render_template(const char *name, const char *template_str) {
    if (template_str == NULL || name == NULL) return "Template Error";

    char buffer[256];
    snprintf(buffer, sizeof(buffer), template_str, name);
    return strdup(buffer);
}

char* render_response_from_env(Environment *env) {
    const char *name = get_name(env);
    const char *rendered_template = render_template(name, env->template);

    char *response = malloc(strlen(rendered_template) + 1);
    if (response != NULL) {
        strcpy(response, rendered_template);
    }
    
    free((void*)rendered_template);
    return response;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "Alice", .template = "Hello, %s!" };
    char* response = home(&env);

    printf("%s\n", response);
    free(response);
    
    return 0;
}