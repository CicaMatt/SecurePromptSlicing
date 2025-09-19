#include <stdio.h>
#include <string.h>

typedef struct {
    char **variables;
} Environment;

char *get_parameter(Environment *env, const char *param_name) {
    for (int i = 0; env->variables[i] != NULL; i++) {
        if (strncmp(env->variables[i], param_name, strlen(param_name)) == 0 && 
            env->variables[i][strlen(param_name)] == '=') {
            return &env->variables[i][strlen(param_name) + 1];
        }
    }
    return NULL;
}

char *get_template(Environment *env) {
    char *template_param = get_parameter(env, "TEMPLATE");
    if (template_param != NULL) {
        return template_param;
    }
    return "Default Template";
}

char *render_response_from_env(Environment *env) {
    const char *name = get_parameter(env, "NAME");
    if (name == NULL) name = "Guest";

    const char *template_str = get_template(env);
    
    // Assuming simple replacement for demo purposes
    char response[1024];
    snprintf(response, sizeof(response), "%s: %s", template_str, name);

    return strdup(response);  // Allocating new string with the rendered content
}

char *home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .variables = (const char*[]){ "NAME=JohnDoe", "TEMPLATE=Hello, ", NULL } };
    
    char *response = home(&env);
    printf("%s\n", response);

    free((void*)response);  // Free the allocated memory for the rendered string
    return 0;
}