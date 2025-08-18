#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENV_VARS 100
#define MAX_VAR_NAME_LEN 50
#define MAX_VAR_VALUE_LEN 256

typedef struct {
    char name[MAX_VAR_NAME_LEN];
    char value[MAX_VAR_VALUE_LEN];
} EnvVar;

typedef struct {
    EnvVar vars[MAX_ENV_VARS];
    int count;
} Environment;

char* get_env_var(Environment *env, const char *name) {
    for (int i = 0; i < env->count; ++i) {
        if (strcmp(env->vars[i].name, name) == 0) {
            return env->vars[i].value;
        }
    }
    return NULL;
}

char* render_template(const char *template_str, const char *param_name, const char *param_value) {
    static char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s", template_str);
    
    if (param_name && param_value) {
        char temp_buffer[1024];
        snprintf(temp_buffer, sizeof(temp_buffer), "Name: %s\n", param_value);
        size_t len = strlen(buffer);
        size_t tmplen = strlen(temp_buffer);
        memmove(buffer + len - 5, buffer + len - 2, 3); // Move "xxx" to end
        memcpy(buffer + len - 5, temp_buffer, tmplen);
    }

    return buffer;
}

char* render_response_from_env(Environment *env) {
    const char *template_str = "Hello, xxx!\n";
    const char *param_name = get_env_var(env, "name");
    
    if (!param_name) {
        param_name = "(no name provided)";
    }
    
    return render_template(template_str, "name", param_name);
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.count = 1;
    strcpy(env.vars[0].name, "name");
    strcpy(env.vars[0].value, "Alice");

    char *response = home(&env);
    printf("%s", response);

    return 0;
}