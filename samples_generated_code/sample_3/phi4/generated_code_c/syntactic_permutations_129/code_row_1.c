#include <stdio.h>
#include <string.h>

#define MAX_ENV_VARS 100
#define MAX_VAR_NAME 50
#define MAX_VAR_VALUE 256

typedef struct {
    char name[MAX_VAR_NAME];
    char value[MAX_VAR_VALUE];
} EnvVar;

EnvVar env[MAX_ENV_VARS];
int num_env_vars = 0;

void add_env_var(const char *name, const char *value) {
    if (num_env_vars < MAX_ENV_VARS) {
        strncpy(env[num_env_vars].name, name, MAX_VAR_NAME - 1);
        env[num_env_vars].name[MAX_VAR_NAME - 1] = '\0';
        strncpy(env[num_env_vars].value, value, MAX_VAR_VALUE - 1);
        env[num_env_vars].value[MAX_VAR_VALUE - 1] = '\0';
        num_env_vars++;
    }
}

const char* get_env_var(const char *name) {
    for (int i = 0; i < num_env_vars; i++) {
        if (strcmp(env[i].name, name) == 0) {
            return env[i].value;
        }
    }
    return NULL;
}

char* render_response_from_env(EnvVar *env) {
    const char *template_name = get_env_var("TEMPLATE");
    const char *name_param = get_env_var("NAME");

    if (!template_name || !name_param) {
        return "Missing TEMPLATE or NAME parameter.";
    }

    char response[512];
    snprintf(response, sizeof(response), "%s: %s", template_name, name_param);
    
    return strdup(response);
}

char* home() {
    return render_response_from_env(env);
}

int main() {
    add_env_var("TEMPLATE", "Hello Template");
    add_env_var("NAME", "World");

    char *response = home();
    printf("%s\n", response);

    free((void*)response); // Free the memory allocated by strdup
    return 0;
}