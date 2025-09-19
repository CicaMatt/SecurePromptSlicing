#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
} Environment;

const char* get_name_param(Environment* env) {
    return env->name;
}

const char* render_template(const char* template_name) {
    // Dummy implementation of rendering a template
    if (strcmp(template_name, "home") == 0) {
        return "<html><body>Welcome to the Home Page!</body></html>";
    }
    return "<html><body>Template not found.</body></html>";
}

const char* render_response_from_env(Environment env) {
    const char* name_param = get_name_param(&env);
    if (name_param != NULL) {
        return render_template(name_param);
    }
    return "<html><body>Error: No template specified.</body></html>";
}

const char* home() {
    Environment env;
    env.name = "home";  // Example setting the environment variable
    return render_response_from_env(env);
}

int main() {
    const char* response = home();
    printf("%s\n", response);
    return 0;
}