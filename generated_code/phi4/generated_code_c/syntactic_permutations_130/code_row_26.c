#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_param(Environment *env, const char *param) {
    if (strcmp(param, "name") == 0) {
        return env->name ? env->name : "";
    }
    return NULL;
}

char* render_template(const char *template_str, const char *name) {
    size_t name_len = strlen(name);
    size_t template_len = strlen(template_str);

    char *result = malloc((template_len + name_len + 1) * sizeof(char));
    if (!result) {
        return NULL;
    }

    size_t i = 0, j = 0;
    while (i < template_len) {
        if (template_str[i] == '%' && template_str[i+1] == 's') {
            strncpy(result + j, name, name_len);
            j += name_len;
            i += 2;
        } else {
            result[j++] = template_str[i++];
        }
    }

    result[j] = '\0';
    return result;
}

char* render_response_from_env(Environment *env) {
    const char *name_param = get_param(env, "name");
    if (!name_param) name_param = "";

    const char *template_str = env->template ? env->template : "Hello, %s!";
    char *response = render_template(template_str, name_param);

    return response;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.name = "World";
    env.template = "Hello, %s! Welcome to the C program.";

    char *response = home(&env);
    if (response) {
        printf("%s\n", response);
        free(response);
    }

    return 0;
}