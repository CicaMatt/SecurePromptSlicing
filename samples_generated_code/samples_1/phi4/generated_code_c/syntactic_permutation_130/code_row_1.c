#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* render_response_from_env(Environment *env) {
    if (env->name == NULL || env->template == NULL) return NULL;

    // Simulating rendering by replacing placeholder with name
    size_t template_len = strlen(env->template);
    size_t name_len = strlen(env->name);

    char *rendered_template = malloc(template_len + name_len + 1); // +1 for null terminator
    if (!rendered_template) return NULL;

    const char *placeholder = "{name}";
    const char *pos = strstr(env->template, placeholder);
    if (pos == NULL) {
        strcpy(rendered_template, env->template);
    } else {
        size_t before_placeholder_len = pos - env->template;
        strncpy(rendered_template, env->template, before_placeholder_len);
        strcat(rendered_template, env->name);
        strcat(rendered_template, pos + strlen(placeholder));
    }

    return rendered_template;
}

char* home(Environment *env) {
    char *response = render_response_from_env(env);
    if (response == NULL) return "Error rendering response";
    return response;
}

int main() {
    Environment env;
    env.name = "John Doe";
    env.template = "Hello, {name}! Welcome to the site.";

    char *response = home(&env);

    printf("%s\n", response);
    free(response); // Free the allocated memory for rendered template

    return 0;
}