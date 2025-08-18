#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

const char* get_request_parameter(Environment* env, const char* param) {
    if (strcmp(param, "name") == 0 && env->name != NULL) {
        return env->name;
    }
    return NULL;
}

char* render_template(const char* template_str, const char* name_param) {
    char *rendered = malloc(strlen(template_str) + strlen(name_param) + 1);
    if (rendered == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    sprintf(rendered, "%s %s", template_str, name_param);
    return rendered;
}

char* render_response_from_env(Environment* env) {
    const char *name = get_request_parameter(env, "name");
    if (name == NULL || env->template == NULL) {
        return strdup("Error: Missing parameters.");
    }
    
    char *rendered_template = render_template(env->template, name);
    return rendered_template;
}

void home(Environment* env) {
    char* response = render_response_from_env(env);
    printf("%s\n", response);
    free(response);
}

int main() {
    Environment env;
    env.name = "John Doe";
    env.template = "Hello, ";
    
    home(&env);

    return 0;
}