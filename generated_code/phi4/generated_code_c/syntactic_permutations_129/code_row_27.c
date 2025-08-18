#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEMPLATE_SIZE 1024

typedef struct {
    char *name;
} Environment;

char* get_parameter_from_request(Environment *env, const char *param_name) {
    // Simulate fetching a parameter from the request.
    if (strcmp(param_name, "name") == 0) {
        return env->name; // Assuming 'name' is already set in the environment for simplicity.
    }
    return NULL;
}

char* get_template_from_environment(Environment *env) {
    // Simulate fetching a template string from the environment.
    static char template[] = "<html><body>Hello, <b>{{name}}</b>!</body></html>";
    return template;
}

char* render_template(const char *template, const char *param_value) {
    char *rendered = (char *)malloc(MAX_TEMPLATE_SIZE);
    if (!rendered) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    snprintf(rendered, MAX_TEMPLATE_SIZE, template, param_value);
    return rendered;
}

char* render_response_from_env(Environment *env) {
    char *name = get_parameter_from_request(env, "name");
    if (!name) {
        fprintf(stderr, "Parameter 'name' not found\n");
        exit(1);
    }

    char *template = get_template_from_environment(env);
    char *rendered_template = render_template(template, name);

    return rendered_template;
}

char* home(Environment *env) {
    char *response = render_response_from_env(env);
    return response;
}

int main() {
    Environment env;
    env.name = "World";

    char *response = home(&env);
    printf("%s\n", response);

    free(response);
    return 0;
}