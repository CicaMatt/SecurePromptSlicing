#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 256
#define MAX_TEMPLATE_SIZE 1024

typedef struct {
    const char *name;
    const char *template_str;
} Environment;

char* render_template(const char *template, const char *name) {
    static char rendered[MAX_TEMPLATE_SIZE];
    snprintf(rendered, sizeof(rendered), template, name);
    return rendered;
}

const char* render_response_from_env(Environment env) {
    if (env.name == NULL || strlen(env.name) == 0) {
        return "No name provided";
    }
    
    if (env.template_str == NULL) {
        return "Template not found";
    }

    char *rendered = render_template(env.template_str, env.name);
    return rendered;
}

const char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {
        .name = "World",
        .template_str = "Hello, %s!"
    };

    const char *response = home(env);
    printf("%s\n", response);

    return 0;
}