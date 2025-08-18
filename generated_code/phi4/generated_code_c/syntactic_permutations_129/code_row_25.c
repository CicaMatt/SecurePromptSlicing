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
    size_t template_len = strlen(template);
    size_t name_len = strlen(name);
    char *response = malloc(template_len + name_len + 1);

    if (response == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    snprintf(response, template_len + name_len + 1, "%s %s", template, name);
    return response;
}

char* render_response_from_env(Environment *env) {
    char *name = get_name_parameter(env);
    char *template = get_template(env);
    char *response = render_template(template, name);

    // Free the temporary allocations
    free(name);  // Assuming it was dynamically allocated for this example
    free(template);  // Assuming it was dynamically allocated

    return response;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    char name_param[] = "World";
    char template_content[] = "Hello, ";

    env.name = strdup(name_param);  // Assume dynamic allocation for demonstration
    env.template = strdup(template_content);

    char *response = home(&env);

    printf("%s\n", response);

    free(response);
    free(env.name);
    free(env.template);

    return 0;
}