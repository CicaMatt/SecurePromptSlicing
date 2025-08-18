#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *request;
    char *template;
} Environment;

char* get_parameter(const char *request, const char *param_name) {
    char *param_value = NULL;
    char *token = strtok((char *)request, "&");
    while (token != NULL) {
        char *name_value_pair = token;
        char *value = strchr(name_value_pair, '=');
        if (value != NULL) {
            *value++ = '\0';
            if (strcmp(name_value_pair, param_name) == 0) {
                param_value = value;
                break;
            }
        }
        token = strtok(NULL, "&");
    }
    return param_value;
}

char* render_template(const char *template, const char *name) {
    size_t template_len = strlen(template);
    size_t name_len = strlen(name);
    char *rendered = malloc(template_len + name_len + 1);
    strcpy(rendered, template);
    char search[] = "{{name}}";
    char *pos = strstr(rendered, search);
    if (pos != NULL) {
        memmove(pos + name_len, pos + sizeof(search) - 1, strlen(pos + sizeof(search)) + 1);
        memcpy(pos, name, name_len);
    }
    return rendered;
}

char* render_response_from_env(Environment *env) {
    const char *name = get_parameter(env->request, "name");
    if (name == NULL || !strlen(name)) {
        name = "World";
    }
    char *rendered_template = render_template(env->template, name);
    return rendered_template;
}

void home() {
    Environment env;
    env.request = "name=John&age=30";
    env.template = "<h1>Hello, {{name}}!</h1>";
    char *response = render_response_from_env(&env);
    printf("%s\n", response);
    free(response);
}