#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Environment;

char* get_template_from_env(Environment *env) {
    return "Welcome, %s!";
}

char* render_template_with_name(const char *template, const char *name) {
    size_t template_len = strlen(template);
    size_t name_len = strlen(name);
    
    // Allocate enough space for both strings and the format specifier
    char *rendered = (char *)malloc(template_len + name_len + 2); 
    if (!rendered) return NULL;

    snprintf(rendered, template_len + name_len + 2, template, name);
    return rendered;
}

const char* render_response_from_env(Environment *env) {
    const char *name_param = env->name; // Assuming `name` is already set in Environment
    if (!name_param) return "No Name Provided";

    const char *template = get_template_from_env(env);
    char *response = render_template_with_name(template, name_param);
    
    return response ? response : "Rendering Error";
}

const char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.name = "Alice";

    const char *response = home(&env);
    printf("%s\n", response);

    free((void*)response); // Free the memory allocated by render_template_with_name

    return 0;
}