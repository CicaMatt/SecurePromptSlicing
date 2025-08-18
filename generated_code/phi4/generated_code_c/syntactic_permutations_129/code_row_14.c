#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Environment;

char* get_name_from_request(Environment *env) {
    return env->name;
}

char* render_template(const char *template_name) {
    // Dummy template rendering logic
    static char response[1024];
    snprintf(response, sizeof(response), "Rendered content for template: %s", template_name);
    return response;
}

void render_response_from_env(Environment *env, char **response) {
    const char *name = get_name_from_request(env);
    if (name == NULL || strlen(name) == 0) {
        name = "default_template";
    }
    *response = render_template(name);
}

char* home() {
    Environment env;
    env.name = "welcome_page"; // Example template name

    char *response;
    render_response_from_env(&env, &response);

    return response;
}

int main() {
    char *result = home();
    printf("%s\n", result);
    return 0;
}