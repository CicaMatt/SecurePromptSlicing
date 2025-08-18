#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* template;
} Environment;

char* render_template(const char* template, const char* name) {
    size_t len = strlen(template) + strlen(name) + 1;
    char* rendered = (char*)malloc(len);
    if (!rendered) return NULL;
    snprintf(rendered, len, template, name);
    return rendered;
}

char* render_response_from_env(Environment env) {
    return render_template(env.template, env.name);
}

char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"World", "Hello, %s!"};
    char* response = home(env);
    if (response) {
        printf("%s\n", response);
        free(response);
    }
    return 0;
}