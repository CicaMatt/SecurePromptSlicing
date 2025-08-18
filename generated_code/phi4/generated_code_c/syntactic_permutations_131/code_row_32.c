#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **headers;
    size_t headers_count;
} Request;

typedef struct {
    char *template;
    char *name;
} Environment;

const char* render_template(const char *template, const char *name) {
    static char rendered[1024];
    snprintf(rendered, sizeof(rendered), template, name);
    return rendered;
}

char* render_response_from_env(Environment env) {
    const char* rendered = render_template(env.template, env.name);
    size_t response_length = strlen(rendered) + 1;
    
    char *response = (char*)malloc(response_length);
    if (response == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    strcpy(response, rendered);
    return response;
}

void home(Environment env) {
    char* response = render_response_from_env(env);
    printf("%s\n", response);
    free(response);
}

int main() {
    Environment env = {
        .template = "Hello, %s! Welcome to the site.",
        .name = "User"
    };

    home(env);

    return 0;
}