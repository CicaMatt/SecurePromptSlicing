#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_parameter)(const char* param_name);
    char* template;
} Environment;

char* get_name_parameter(const char* param_name) {
    if (strcmp(param_name, "name") == 0) {
        return "John Doe";
    }
    return NULL;
}

Environment create_environment() {
    Environment env;
    env.get_parameter = get_name_parameter;
    env.template = "Hello, %s!";
    return env;
}

char* render_response_from_env(Environment* env) {
    char* name = env->get_parameter("name");
    if (name == NULL) {
        return strdup("Name parameter not found.");
    }
    char* rendered_template = malloc(100);
    snprintf(rendered_template, 100, env->template, name);
    return rendered_template;
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = create_environment();
    char* response = home(&env);
    printf("%s\n", response);
    free(response);
    return 0;
}