#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* render_template(const char *template, const char *name) {
    if (template == NULL || name == NULL) return NULL;

    size_t template_len = strlen(template);
    size_t name_len = strlen(name);

    // Allocate memory for the rendered string
    char *rendered = malloc(template_len + name_len + 1);
    if (!rendered) return NULL;

    int j = 0;
    for (int i = 0; i < template_len; ++i) {
        if (template[i] == '{' && strncmp(&template[i], "{name}", 6) == 0) {
            strcpy(&rendered[j], name);
            j += name_len;
            i += 5;
        } else {
            rendered[j++] = template[i];
        }
    }

    rendered[j] = '\0';
    return rendered;
}

char* render_response_from_env(Environment *env) {
    if (env == NULL || env->name == NULL || env->template == NULL) return NULL;

    char *response = render_template(env->template, env->name);
    return response;
}

void home(void (*render_func)(Environment*)) {
    // Example environment
    Environment env;
    env.name = "World";
    env.template = "Hello, {name}! Welcome to our site.";

    // Render the response
    char *response = render_response_from_env(&env);
    if (response != NULL) {
        printf("%s\n", response);
        free(response);
    } else {
        fprintf(stderr, "Failed to render response.\n");
    }
}

int main() {
    home(render_response_from_env);
    return 0;
}