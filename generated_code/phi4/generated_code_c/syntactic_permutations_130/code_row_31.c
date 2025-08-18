#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 1;
    char *rendered = malloc(len);
    
    if (rendered == NULL) {
        return NULL;
    }
    
    snprintf(rendered, len, "%s%s", template, name);
    return rendered;
}

char* render_response_from_env(const Environment *env) {
    const char *name_param = "Anonymous";
    if (env->name != NULL) {
        name_param = env->name;
    }

    char *rendered_template = render_template(env->template, name_param);
    
    if (rendered_template == NULL) {
        return strdup("Error rendering template");
    }
    
    return rendered_template;
}

void home(Environment *env) {
    char *response = render_response_from_env(env);
    printf("%s\n", response);
    free(response);  // Free the allocated memory for the response
}

int main() {
    Environment env;
    env.name = "John Doe";
    env.template = "Hello, ";

    home(&env);

    return 0;
}