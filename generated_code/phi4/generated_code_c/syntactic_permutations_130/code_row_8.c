#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* template_str;
} Environment;

const char* render_template(const char* template_str, const char* name) {
    if (template_str == NULL || name == NULL) return "";
    
    size_t buf_size = strlen(template_str) + strlen(name) + 1;
    char* rendered = malloc(buf_size);
    snprintf(rendered, buf_size, template_str, name);
    
    return rendered;
}

const char* render_response_from_env(Environment* env) {
    if (env == NULL || env->name == NULL || env->template_str == NULL) return "";
    
    const char* rendered_template = render_template(env->template_str, env->name);
    return strdup(rendered_template); // Duplicate the string to avoid returning a pointer to local variable
}

const char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.name = "Alice";
    env.template_str = "Hello, %s! Welcome to our site.";

    const char* response = home(&env);
    if (response != NULL) {
        printf("%s\n", response);
        free((void*)response); // Free the duplicated string
    }

    return 0;
}