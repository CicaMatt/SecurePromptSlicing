#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* render_template(const char *template, const char *name) {
    if (template == NULL || name == NULL) return NULL;
    
    size_t len = strlen(template) + strlen(name) + 1;
    char *rendered = malloc(len);
    if (!rendered) return NULL;

    snprintf(rendered, len, template, name);
    return rendered;
}

char* render_response_from_env(Environment env) {
    const char default_template[] = "Hello, %s!";
    
    const char *template = env.template ? env.template : default_template;
    return render_template(template, env.name);
}

char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.name = "World";
    env.template = NULL;  // Use the default template

    char *response = home(env);

    if (response) {
        printf("%s\n", response);
        free(response);
    }

    return 0;
}