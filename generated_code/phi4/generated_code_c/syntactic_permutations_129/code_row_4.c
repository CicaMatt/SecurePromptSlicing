#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_name_parameter(Environment *env) {
    return env->name;
}

char* get_template(Environment *env) {
    return env->template;
}

char* render_template(char *template, const char *name) {
    char *result = malloc(strlen(template) + strlen(name) + 1);
    if (result == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    sprintf(result, template, name);
    return result;
}

char* render_response_from_env(Environment *env) {
    const char *name = get_name_parameter(env);
    char *template = strdup(get_template(env));
    if (template == NULL) {
        perror("Failed to duplicate template");
        exit(EXIT_FAILURE);
    }
    char *response = render_template(template, name);
    free((void*)template); // Free the duplicated string
    return response;
}

char* home(Environment *env) {
    char *response = render_response_from_env(env);
    return response;
}

int main() {
    Environment env;
    env.name = "John Doe";
    env.template = "Hello, %s! Welcome to our site.";

    char *response = home(&env);
    printf("%s\n", response);

    free(response); // Free the allocated memory for the response
    return 0;
}