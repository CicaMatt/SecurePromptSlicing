#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* render_template(const char *template, const char *name) {
    char *result = malloc(strlen(template) + strlen(name) + 1);
    sprintf(result, template, name);
    return result;
}

void free_env(Environment *env) {
    free(env->name);
    free(env->template);
    free(env);
}

char* render_response_from_env(Environment *env) {
    char *rendered_template = render_template(env->template, env->name);
    return rendered_template;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment *env = malloc(sizeof(Environment));
    env->name = strdup("World");
    env->template = strdup("Hello, %s!");

    char *response = home(env);
    printf("%s\n", response);

    free(response);
    free_env(env);

    return 0;
}