#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEMPLATE_SIZE 1024

typedef struct {
    char **variables;
    size_t var_count;
} Environment;

char *get_variable(const Environment *env, const char *name) {
    for (size_t i = 0; i < env->var_count; ++i) {
        if (strncmp(env->variables[i], name, strlen(name)) == 0 && env->variables[i][strlen(name)] == '=') {
            return env->variables[i] + strlen(name) + 1;
        }
    }
    return NULL;
}

char *render_template(const char *template_str, const Environment *env) {
    static char rendered[MAX_TEMPLATE_SIZE];
    char buffer[MAX_TEMPLATE_SIZE];
    const char *start = template_str;
    char *end;

    while ((end = strstr(start, "{{")) != NULL) {
        strncpy(buffer, start, end - start);
        buffer[end - start] = '\0';

        strcat(rendered, buffer);

        if (*(end + 2) == '/') {
            strncat(rendered, get_variable(env, "name"), MAX_TEMPLATE_SIZE - strlen(rendered) - 1);
            start = end + 4;
        } else {
            const char *var_start = end + 2;
            const char *var_end = strstr(var_start, "}}");
            if (var_end != NULL) {
                char var_name[MAX_TEMPLATE_SIZE];
                strncpy(var_name, var_start, var_end - var_start);
                var_name[var_end - var_start] = '\0';

                strcat(rendered, get_variable(env, var_name));
                start = var_end + 2;
            }
        }
    }

    strcpy(rendered + strlen(rendered), start);
    return rendered;
}

char *render_response_from_env(const Environment *env) {
    const char template[] = "<html><body>Hello, {{name}}!</body></html>";
    return render_template(template, env);
}

char *home() {
    Environment env;
    env.variables = (char **)malloc(2 * sizeof(char *));
    env.variables[0] = strdup("name=John Doe");
    env.var_count = 1;

    char *response = render_response_from_env(&env);

    free(env.variables[0]);
    free(env.variables);
    return response;
}

int main() {
    char *response = home();
    printf("%s\n", response);
    return 0;
}