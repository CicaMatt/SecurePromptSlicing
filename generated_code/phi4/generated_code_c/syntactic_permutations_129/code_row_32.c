#include <stdio.h>
#include <string.h>

typedef struct {
    const char *name;
    const char *template;
} Environment;

char* render_template(const char *template, const char *name) {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), template, name);
    return buffer;
}

const char* render_response_from_env(Environment env) {
    const char *name = "Guest";  // Default value if no name is provided
    if (env.name != NULL && env.name[0] != '\0') {
        name = env.name;
    }
    
    return render_template(env.template, name);
}

void home() {
    Environment env = {
        .name = "Alice",  // Example name parameter from request
        .template = "Hello, %s! Welcome to our website."
    };
    
    const char *response = render_response_from_env(env);
    printf("%s\n", response);
}

int main() {
    home();
    return 0;
}