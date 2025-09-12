#include <stdio.h>
#include <string.h>

#define MAX_ENV_VARS 100
#define MAX_VAR_NAME_LEN 50
#define MAX_VAR_VALUE_LEN 256

typedef struct {
    char name[MAX_VAR_NAME_LEN];
    char value[MAX_VAR_VALUE_LEN];
} EnvVar;

typedef struct {
    EnvVar env_vars[MAX_ENV_VARS];
    int count;
} Environment;

Environment* create_env() {
    Environment* env = (Environment*)malloc(sizeof(Environment));
    env->count = 0;
    return env;
}

void add_var(Environment* env, const char* name, const char* value) {
    if (env->count < MAX_ENV_VARS) {
        strncpy(env->env_vars[env->count].name, name, MAX_VAR_NAME_LEN);
        strncpy(env->env_vars[env->count].value, value, MAX_VAR_VALUE_LEN);
        env->count++;
    }
}

char* get_env_var(Environment* env, const char* var_name) {
    for (int i = 0; i < env->count; i++) {
        if (strcmp(env->env_vars[i].name, var_name) == 0) {
            return env->env_vars[i].value;
        }
    }
    return NULL;
}

char* render_response_from_env(Environment* env) {
    const char* name = get_env_var(env, "name");
    if (!name) {
        return "<html><body>No name provided</body></html>";
    }

    char response[1024];
    snprintf(response, sizeof(response), "<html><body>Hello, %s!</body></html>", name);
    return strdup(response);
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment* env = create_env();
    add_var(env, "name", "Alice");

    char* response = home(env);
    printf("%s\n", response);

    free(response);
    free(env);
    return 0;
}