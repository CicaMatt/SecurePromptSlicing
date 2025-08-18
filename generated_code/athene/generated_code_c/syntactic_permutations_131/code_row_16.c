#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Environment;

char* get_parameter(Environment *env, const char *param_name) {
    if (strcmp(param_name, "name") == 0 && env->name != NULL) {
        return env->name;
    }
    return "";
}

char* render_template(const char *template, const char *name) {
    char *response = malloc(strlen(template) + strlen(name) + 1);
    sprintf(response, template, name);
    return response;
}

char* render_response_from_env(Environment *env) {
    const char *template = "Hello, %s!";
    char *name = get_parameter(env, "name");
    return render_template(template, name);
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.name = "World";
    char *response = home(&env);
    printf("%s\n", response);
    free(response); // Free the allocated memory
    return 0;
}