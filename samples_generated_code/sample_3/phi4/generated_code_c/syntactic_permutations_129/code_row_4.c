#include <stdio.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* render_template(const char *template, const char *name) {
    static char buffer[1024];
    snprintf(buffer, sizeof(buffer), template, name);
    return buffer;
}

const char* render_response_from_env(Environment env) {
    char *response = render_template(env.template, env.name ? env.name : "Guest");
    printf("Rendered Response: %s\n", response);
    return response;
}

const char* home() {
    Environment env = { .name = "John Doe", .template = "Hello, %s!" };
    return render_response_from_env(env);
}

int main() {
    const char *response = home();
    printf("Response: %s\n", response);
    return 0;
}