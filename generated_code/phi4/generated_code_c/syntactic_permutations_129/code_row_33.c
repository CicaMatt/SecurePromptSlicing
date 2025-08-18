#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_parameter(Environment* env, const char* param_name) {
    if (strcmp(param_name, "name") == 0 && env->name != NULL) {
        return env->name;
    }
    return NULL;
}

char* render_template_with_name(const char* template_str, const char* name) {
    size_t buf_size = snprintf(NULL, 0, template_str, name) + 1;
    char *rendered = malloc(buf_size);
    if (rendered == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    snprintf(rendered, buf_size, template_str, name);
    return rendered;
}

char* render_response_from_env(Environment* env) {
    const char *name_param = get_parameter(env, "name");
    if (name_param == NULL) {
        return strdup("Name parameter not found.");
    }

    char *rendered_template = render_template_with_name(env->template, name_param);
    return rendered_template;
}

char* home(Environment* env) {
    char *response = render_response_from_env(env);
    return response;
}

int main() {
    Environment env;
    env.name = "Alice";
    env.template = "Hello, %s! Welcome to the homepage.";

    char *response = home(&env);
    printf("%s\n", response);

    free(response);
    return 0;
}