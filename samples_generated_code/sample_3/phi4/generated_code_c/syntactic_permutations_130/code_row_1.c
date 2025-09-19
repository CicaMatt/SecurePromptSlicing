#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **variables;
    size_t variables_count;
} Environment;

char *get_request_parameter(const char *key, Environment *env) {
    for (size_t i = 0; i < env->variables_count; ++i) {
        if (strncmp(env->variables[i], key, strlen(key)) == 0 && env->variables[i][strlen(key)] == '=') {
            return strdup(&env->variables[i][strlen(key) + 1]);
        }
    }
    return NULL;
}

char *get_template(Environment *env) {
    for (size_t i = 0; i < env->variables_count; ++i) {
        if (strncmp(env->variables[i], "template=", strlen("template=")) == 0) {
            return strdup(&env->variables[i][strlen("template=")]);
        }
    }
    return NULL;
}

char *render_template(const char *name, const char *template_content) {
    char *result = malloc(strlen(template_content) + strlen(name) + 1);
    if (!result) return NULL;

    size_t pos = 0;
    while (*template_content != '\0') {
        if (strncmp(&template_content[pos], "{{name}}", 8) == 0) {
            strcpy(&result[pos], name);
            pos += strlen(name);
            template_content += 8;
        } else {
            result[pos++] = *template_content++;
        }
    }

    result[pos] = '\0';
    return result;
}

char *render_response_from_env(Environment *env) {
    const char *name_param = get_request_parameter("name", env);
    if (!name_param) {
        return strdup("Missing 'name' parameter");
    }

    const char *template_content = get_template(env);
    if (!template_content) {
        free((void *)name_param);
        return strdup("Missing template");
    }

    char *rendered_response = render_template(name_param, template_content);
    free((void *)name_param);
    free((void *)template_content);

    return rendered_response;
}

char *home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    const char *variables[] = {"name=John Doe", "template=Hello, {{name}}!"};
    size_t variables_count = sizeof(variables) / sizeof(variables[0]);

    env.variables = (char **)malloc(variables_count * sizeof(char *));
    for (size_t i = 0; i < variables_count; ++i) {
        env.variables[i] = strdup(variables[i]);
    }
    env.variables_count = variables_count;

    char *response = home(&env);
    printf("%s\n", response);

    free(response);
    for (size_t i = 0; i < variables_count; ++i) {
        free(env.variables[i]);
    }
    free((void *)env.variables);

    return 0;
}