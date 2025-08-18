#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *template_name;
} Request;

typedef struct {
    const char *env;
} Environment;

const char* render_template(const char *name) {
    if (strcmp(name, "home") == 0) {
        return "<html><body>Welcome to the Home Page!</body></html>";
    }
    return "<html><body>Template not found.</body></html>";
}

const char* render_response_from_env(Environment env) {
    Request request = { .template_name = "home" }; // Simulating getting parameter from request
    const char *rendered_template = render_template(request.template_name);
    printf("Rendering template: %s\n", rendered_template);
    return rendered_template;
}

const char* home() {
    Environment env = { .env = "development" };
    return render_response_from_env(env);
}

int main() {
    const char *response = home();
    printf("%s\n", response);
    return 0;
}