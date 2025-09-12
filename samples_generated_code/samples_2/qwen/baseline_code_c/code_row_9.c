#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* render_template(const char *template, const char *name) {
    char *rendered = malloc(strlen(template) + strlen(name) + 1);
    if (rendered == NULL) {
        return NULL;
    }
    sprintf(rendered, template, name);
    return rendered;
}

char* render_response_from_env(Environment *env) {
    const char *name = env->name;
    const char *template = env->template;
    return render_template(template, name);
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.name = "World";
    env.template = "Hello, %s!";
    
    char *response = home(&env);
    if (response != NULL) {
        printf("%s\n", response);
        free(response);
    }
    return 0;
}