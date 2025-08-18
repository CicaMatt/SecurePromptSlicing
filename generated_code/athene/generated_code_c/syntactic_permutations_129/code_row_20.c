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

void render_response(const char *template, const char *name, char **response) {
    size_t len = strlen(template) + strlen(name) + 1;
    *response = malloc(len);
    if (*response == NULL) exit(EXIT_FAILURE);
    snprintf(*response, len, template, name);
}

char* render_response_from_env(Environment *env) {
    const char *template = "Hello, %s!";
    const char *name = get_parameter(env, "name");
    char *response;
    render_response(template, name, &response);
    return response;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "World" };
    char *response = home(&env);
    printf("%s\n", response);
    free(response);
    return 0;
}