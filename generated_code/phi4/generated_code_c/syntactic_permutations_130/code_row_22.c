#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_parameter(Environment *env, const char *key) {
    if (strcmp(key, "name") == 0) return env->name;
    return NULL;
}

char* get_template(Environment *env) {
    return env->template;
}

char* render_response_from_env(Environment *env) {
    char *name = get_parameter(env, "name");
    char *template = get_template(env);
    
    if (name == NULL || template == NULL) {
        return "<html><body>Error: Missing parameters or template.</body></html>";
    }
    
    char *response = malloc(strlen(template) + strlen(name) + 1);
    sprintf(response, template, name);

    return response;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.name = "John Doe";
    env.template = "<html><body>Hello, %s!</body></html>";

    char *response = home(&env);
    printf("%s\n", response);

    free(response);
    return 0;
}