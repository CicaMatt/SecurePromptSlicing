#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* fetch_param(const Environment* env, const char* param_name) {
    if (strcmp(param_name, "name") == 0) {
        return env->name ? strdup(env->name) : NULL;
    }
    return NULL;
}

char* fetch_template(const Environment* env) {
    return env->template ? strdup(env->template) : NULL;
}

char* render_response_from_env(const Environment* env) {
    char *name = fetch_param(env, "name");
    char *template = fetch_template(env);

    if (!name || !template) {
        return strdup("Error: Missing parameter or template.");
    }

    // Simple substitution for demonstration purposes
    char *response = malloc(strlen(template) + strlen(name) + 1);
    if (response == NULL) {
        free(name);
        free(template);
        return strdup("Error: Memory allocation failed.");
    }
    
    sprintf(response, "%s", template);
    size_t pos;
    for (pos = 0; response[pos] != '\0'; ++pos) {
        if (response[pos] == '%' && response[pos + 1] == 'n') {
            memmove(response + pos, name, strlen(name));
            pos += strlen(name) - 1;
        }
    }

    free(name);
    free(template);

    return response;
}

char* home(const Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {
        .name = "World",
        .template = "Hello, %n!"
    };

    char *response = home(&env);
    printf("%s\n", response);

    free(response);
    return 0;
}