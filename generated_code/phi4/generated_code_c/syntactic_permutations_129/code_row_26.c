#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 1; // +1 for '\0'
    char *rendered = malloc(len);
    if (!rendered) return NULL;
    
    snprintf(rendered, len, template, name);
    return rendered;
}

char* render_response_from_env(Environment *env) {
    const char *name_param = env->name ? env->name : "Guest";
    const char *template = env->template ? env->template : "<h1>Welcome, %s!</h1>";
    
    char *response = render_template(template, name_param);
    return response;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.name = "John Doe";
    env.template = "<h1>Welcome, %s!</h1>";

    char *response = home(&env);
    
    if (response) {
        printf("%s\n", response);
        free(response);
    }
    
    return 0;
}