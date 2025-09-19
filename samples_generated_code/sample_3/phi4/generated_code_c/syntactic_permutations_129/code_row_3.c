#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_request_parameter(Environment *env, const char *param) {
    if (strcmp(param, "name") == 0) {
        return env->name;
    }
    return NULL;
}

char* get_template_from_env(Environment *env) {
    return env->template;
}

char* render_response(char *template, char *name) {
    size_t tmpl_len = strlen(template);
    size_t name_len = strlen(name);
    
    char *response = malloc(tmpl_len + name_len + 2); // extra space for '{' '}' and null terminator
    if (response == NULL) {
        return NULL;
    }
    
    snprintf(response, tmpl_len + name_len + 2, template, name);
    return response;
}

char* render_response_from_env(Environment *env) {
    char *name = get_request_parameter(env, "name");
    char *template = get_template_from_env(env);

    if (name == NULL || template == NULL) {
        return strdup("Invalid request parameters or template.");
    }

    char *response = render_response(template, name);
    free(name); // Free the dynamically allocated memory for `name` in env
    return response;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    
    env.name = strdup("John Doe");
    env.template = strdup("Hello, {name}!");
    
    char *response = home(&env);

    printf("%s\n", response);

    free(env.name);
    free(env.template);
    free(response);

    return 0;
}