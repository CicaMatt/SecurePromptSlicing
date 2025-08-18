#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* template;
} Environment;

char* get_parameter(Environment* env, const char* param_name) {
    if (strcmp(param_name, "name") == 0) {
        return env->name;
    }
    return NULL;
}

char* render_template(const char* template, const char* name) {
    char* rendered = malloc(strlen(template) + strlen(name) + 1);
    sprintf(rendered, template, name);
    return rendered;
}

char* render_response_from_env(Environment* env) {
    const char* name = get_parameter(env, "name");
    if (name == NULL) {
        return strdup("Name parameter not found");
    }
    char* response = render_template(env->template, name);
    return response;
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.name = "World";
    env.template = "Hello, %s!";

    char* response = home(&env);
    printf("%s\n", response);

    free(response);
    return 0;
}