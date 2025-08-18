#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_template(Environment *env) {
    return env->template;
}

char* render_template(const char *name, const char *template) {
    size_t name_len = strlen(name);
    size_t template_len = strlen(template);

    char *rendered = malloc(sizeof(char) * (template_len + name_len + 1));
    if (!rendered) return NULL;

    strcpy(rendered, template);
    for(size_t i = 0; i < template_len; ++i) {
        if(template[i] == '{' && strncmp(&template[i+1], "name", 4) == 0 && template[i+5] == '}') {
            memcpy(&rendered[i], name, name_len);
            memmove(&rendered[i + name_len], &rendered[i + 6], strlen(&rendered[i + 6]) + 1);
        }
    }

    return rendered;
}

char* render_response_from_env(Environment *env) {
    const char *name = env->name ? env->name : "";
    const char *template = get_template(env);

    if (!template) return NULL;

    return render_template(name, template);
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"Alice", "Hello, {name}!"};
    
    char *response = home(&env);
    if (response) {
        printf("%s\n", response);
        free(response);
    } else {
        fprintf(stderr, "Failed to render template.\n");
    }

    return 0;
}