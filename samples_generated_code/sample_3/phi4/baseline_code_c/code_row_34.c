#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    Request request;
    char *template;
} Environment;

char* render_template(const char *template, const char *name) {
    size_t template_len = strlen(template);
    size_t name_len = strlen(name);
    char *rendered = malloc(template_len + name_len + 1); // +1 for null terminator
    if (!rendered) return NULL;
    
    strcpy(rendered, template);
    strcat(rendered, " ");
    strcat(rendered, name);
    
    return rendered;
}

char* render_response_from_env(Environment env) {
    const char *name = env.request.name ? env.request.name : "";
    return render_template(env.template, name);
}

char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.request.name = "John Doe";
    env.template = "Hello, ";

    char *response = home(env);
    if (response) {
        printf("%s\n", response);
        free(response);
    }

    return 0;
}