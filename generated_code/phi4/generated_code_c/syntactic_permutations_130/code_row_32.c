#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENV_MAX_KEY_LEN 256
#define ENV_MAX_VALUE_LEN 256
#define MAX_ENV_VARS 100

typedef struct {
    char key[ENV_MAX_KEY_LEN];
    char value[ENV_MAX_VALUE_LEN];
} EnvVar;

typedef struct {
    EnvVar vars[MAX_ENV_VARS];
    int count;
} Environment;

Environment env = { .count = 0 };

int set_env_var(const char *key, const char *value) {
    if (env.count >= MAX_ENV_VARS) return -1;
    strncpy(env.vars[env.count].key, key, ENV_MAX_KEY_LEN - 1);
    env.vars[env.count].key[ENV_MAX_KEY_LEN - 1] = '\0';
    strncpy(env.vars[env.count].value, value, ENV_MAX_VALUE_LEN - 1);
    env.vars[env.count].value[ENV_MAX_VALUE_LEN - 1] = '\0';
    return env.count++;
}

const char *get_env_var(const char *key) {
    for (int i = 0; i < env.count; ++i) {
        if (strcmp(env.vars[i].key, key) == 0) {
            return env.vars[i].value;
        }
    }
    return NULL;
}

char* render_template_with_name(char *template, const char *name) {
    char *result = malloc(strlen(template) + strlen(name) + 1);
    if (!result) return NULL;

    size_t name_len = strlen(name);
    const char *p = template;
    char *q = result;

    while (*p != '\0') {
        if (strncmp(p, "{{name}}", 8) == 0) {
            strcpy(q, name);
            q += name_len;
            p += 8;
        } else {
            *q++ = *p++;
        }
    }
    *q = '\0';

    return result;
}

char* render_response_from_env(Environment env) {
    const char *template_str = get_env_var("TEMPLATE");
    const char *name_str = get_env_var("NAME");

    if (!template_str || !name_str) {
        return strdup("Error: TEMPLATE or NAME not found in environment.");
    }

    char *rendered_template = render_template_with_name(strdup(template_str), name_str);
    
    if (!rendered_template) {
        return strdup("Error: Failed to render template.");
    }

    return rendered_template;
}

char* home() {
    return render_response_from_env(env);
}

int main() {
    set_env_var("TEMPLATE", "Hello, {{name}}! Welcome to the website.");
    set_env_var("NAME", "John Doe");

    char *response = home();
    printf("%s\n", response);

    free(response);
    return 0;
}