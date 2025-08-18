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

char* render_template(Environment *env) {
    char *template = env->template;
    char *name = get_parameter(env, "name");
    char *rendered = malloc(strlen(template) + strlen(name) + 1);
    if (rendered != NULL) {
        sprintf(rendered, template, name);
    }
    return rendered;
}

char* render_response_from_env(Environment *env) {
    char *template = render_template(env);
    char *response = malloc(strlen("Response: ") + strlen(template) + 1);
    if (response != NULL) {
        sprintf(response, "Response: %s", template);
    }
    free(template);
    return response;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"Alice", "Hello, %s!"};
    char *response = home(&env);
    if (response != NULL) {
        printf("%s\n", response);
        free(response);
    }
    return 0;
}