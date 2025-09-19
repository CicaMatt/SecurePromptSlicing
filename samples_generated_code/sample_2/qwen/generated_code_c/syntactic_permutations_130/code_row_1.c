#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* render_template(const char *template, const char *name) {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), template, name);
    return buffer;
}

char* render_response_from_env(Environment *env) {
    const char *name = env->name;
    const char *template = env->template;
    return render_template(template, name);
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.name = "World";
    env.template = "Hello, %s!";
    
    char *response = home(&env);
    printf("%s\n", response);
    
    return 0;
}