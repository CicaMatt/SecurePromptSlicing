#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    const char *key;
    const char *value;
} EnvVar;

typedef struct {
    EnvVar *vars;
    size_t count;
} Environment;

char* get_env(Environment *env, const char *key) {
    for (size_t i = 0; i < env->count; ++i) {
        if (strcmp(env->vars[i].key, key) == 0) {
            return strdup(env->vars[i].value);
        }
    }
    return NULL;
}

char* render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 15; // Extra space for formatting
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

char* render_response_from_env(Environment *env, Request *req) {
    const char *template = get_env(env, "TEMPLATE");
    if (!template) return NULL;

    char *response = render_template(template, req->name ? req->name : "");
    return response;
}

char* home(Environment *env) {
    Request request = { .name = "World" };
    return render_response_from_env(env, &request);
}

int main() {
    EnvVar env_vars[] = {
        {"TEMPLATE", "Hello, %s! Welcome to our service."}
    };
    Environment env = { .vars = env_vars, .count = 1 };

    char *response = home(&env);
    if (response) {
        printf("%s\n", response);
        free(response);
    }

    return 0;
}