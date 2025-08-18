#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENV_VARS 100

typedef struct {
    char **variables;
} Environment;

Environment create_environment(const char *env_vars[], size_t count) {
    Environment env;
    env.variables = malloc(count * sizeof(char *));
    
    for (size_t i = 0; i < count; ++i) {
        env.variables[i] = strdup(env_vars[i]);
    }
    
    return env;
}

void free_environment(Environment env) {
    for (size_t i = 0; i < MAX_ENV_VARS && env.variables[i]; ++i) {
        free(env.variables[i]);
    }
    free(env.variables);
}

char *get_param(const Environment *env, const char *param_name) {
    size_t len = strlen(param_name);
    for (size_t i = 0; i < MAX_ENV_VARS && env->variables[i]; ++i) {
        if (strncmp(env->variables[i], param_name, len) == 0 && env->variables[i][len] == '=') {
            return strdup(&env->variables[i][len + 1]);
        }
    }
    return NULL;
}

char *render_template(const char *template_str, const char *name) {
    static char buffer[1024];
    
    snprintf(buffer, sizeof(buffer), "Hello, %s!\nThis is your template: %s", name ? name : "Guest", template_str);
    return strdup(buffer);
}

char *render_response_from_env(const Environment *env) {
    const char *name_param = get_param(env, "REQUEST_METHOD=GET&QUERY_STRING=name=");
    
    const char *template_str = get_param(env, "TEMPLATE=");

    if (!template_str) {
        template_str = "<p>Welcome to the home page!</p>";
    }

    return render_template(template_str, name_param);
}

char *home(const Environment *env) {
    return render_response_from_env(env);
}

int main() {
    const char *env_vars[] = {
        "REQUEST_METHOD=GET",
        "QUERY_STRING=name=JohnDoe",
        "TEMPLATE=<h1>Welcome</h1>"
    };
    
    size_t env_count = sizeof(env_vars) / sizeof(char *);
    
    Environment env = create_environment(env_vars, env_count);
    char *response = home(&env);

    printf("%s\n", response);

    free(response);
    free_environment(env);

    return 0;
}