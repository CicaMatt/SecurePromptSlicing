#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **data;
} Environment;

const char* get_parameter(Environment *env, const char *name) {
    for (int i = 0; env->data[i] != NULL; ++i) {
        if (strncmp(env->data[i], name, strlen(name)) == 0 && env->data[i][strlen(name)] == '=') {
            return env->data[i] + strlen(name) + 1;
        }
    }
    return NULL;
}

const char* get_template(Environment *env) {
    for (int i = 0; env->data[i] != NULL; ++i) {
        if (strncmp(env->data[i], "template=", 9) == 0) {
            return env->data[i] + 9;
        }
    }
    return NULL;
}

char* render_template(const char *template, const char *name) {
    char *result = malloc(strlen(template) + strlen(name) + 1);
    if (result != NULL) {
        sprintf(result, template, name);
    }
    return result;
}

const char* render_response_from_env(Environment *env) {
    const char *name_param = get_parameter(env, "name");
    if (name_param == NULL || strlen(name_param) == 0) {
        name_param = "Guest";
    }

    const char *template_str = get_template(env);
    if (template_str == NULL) {
        return "<h1>Hello World</h1>";
    }
    
    char *rendered = render_template(template_str, name_param);
    return rendered;
}

const char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    char *env_data[] = {"name=John", "template=<h1>Hello, %s!</h1>", NULL};
    Environment env = { .data = env_data };

    const char *response = home(&env);
    printf("%s\n", response);

    free((void*)response); // Free the allocated memory for the rendered template

    return 0;
}