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
    size_t count;
} Environment;

Environment env = {0};

void set_env(const char *name, const char *value) {
    if (env.count < MAX_ENV_VARS) {
        strncpy(env.vars[env.count].name, name, MAX_VAR_NAME_LEN - 1);
        strncpy(env.vars[env.count].value, value, MAX_VAR_VALUE_LEN - 1);
        env.count++;
    }
}

const char* get_env_value(const Environment *environment, const char *name) {
    for (size_t i = 0; i < environment->count; ++i) {
        if (strncmp(environment->vars[i].name, name, MAX_VAR_NAME_LEN - 1) == 0) {
            return environment->vars[i].value;
        }
    }
    return NULL;
}

void render_template(const char *template_name, const char *context) {
    printf("Rendering template: %s\n", template_name);
    if (context != NULL) {
        printf("Context: %s\n", context);
    } else {
        printf("No context provided.\n");
    }
}

const char* render_response_from_env(const Environment *environment) {
    const char *template_name = get_env_value(environment, "name");
    if (template_name != NULL) {
        render_template(template_name, template_name);
        return "Template rendered successfully";
    } else {
        return "No name parameter found in environment";
    }
}

const char* home() {
    return render_response_from_env(&env);
}

int main() {
    set_env("name", "home_template");
    
    const char *response = home();
    printf("%s\n", response);

    return 0;
}