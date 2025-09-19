#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_parameter(Environment *env, const char *param) {
    if (strcmp(param, "name") == 0) {
        return env->name;
    }
    return NULL;
}

char* render_template(char *template, const char *name) {
    static char buffer[1024];
    snprintf(buffer, sizeof(buffer), template, name);
    return buffer;
}

void render_response_from_env(Environment *env) {
    char *name = get_parameter(env, "name");
    if (name == NULL || env->template == NULL) {
        printf("Error: Missing parameters\n");
        return;
    }
    
    char *rendered_template = render_template(env->template, name);
    printf("%s\n", rendered_template);
}

void home(Environment *env) {
    render_response_from_env(env);
}

int main() {
    Environment env;
    env.name = "World";
    env.template = "Hello, %s!";
    
    home(&env);

    return 0;
}