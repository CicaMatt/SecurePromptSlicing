#include <stdio.h>
#include <string.h>

#define MAX_ENV_VARS 100
#define MAX_TEMPLATE_LENGTH 1024

typedef struct {
    char name[50];
    char value[256];
} EnvVar;

char* find_env_var(const EnvVar env[], int size, const char *key) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(env[i].name, key) == 0) {
            return env[i].value;
        }
    }
    return NULL;
}

char* render_response_from_env(const EnvVar env[], int size) {
    const char *name_param = find_env_var(env, size, "REQUEST_METHOD");
    const char *template_str = find_env_var(env, size, "TEMPLATE");

    if (name_param == NULL || template_str == NULL) return "Error: Missing parameters.";

    char response[MAX_TEMPLATE_LENGTH];
    snprintf(response, sizeof(response), "Hello, %s!", name_param);
    return strdup(response);
}

char* home(const EnvVar env[], int size) {
    return render_response_from_env(env, size);
}

int main() {
    EnvVar env[] = {
        {"REQUEST_METHOD", "GET"},
        {"TEMPLATE", "Welcome Template"}
    };
    
    int env_size = sizeof(env) / sizeof(EnvVar);

    char* response = home(env, env_size);
    printf("%s\n", response);
    
    free(response);
    return 0;
}