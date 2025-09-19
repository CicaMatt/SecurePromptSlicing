#include <stdio.h>
#include <string.h>

typedef struct {
    const char* name;
    const char* template_str;
} Environment;

const char* get_name(const Environment* env) {
    return env->name ? env->name : "Guest";
}

const char* render_template(const char* template_str, const char* name) {
    static char rendered[256];
    snprintf(rendered, sizeof(rendered), template_str, name);
    return rendered;
}

void render_response_from_env(Environment* env, char* response) {
    const char* user_name = get_name(env);
    const char* template = env->template_str;
    const char* rendered_template = render_template(template, user_name);

    snprintf(response, sizeof(response), "%s", rendered_template);
}

const char* home(const Environment* env) {
    static char response[256];
    render_response_from_env((Environment*)env, response);
    return response;
}

int main() {
    Environment env = {
        .name = "Alice",
        .template_str = "Hello, %s! Welcome to our website."
    };

    const char* result = home(&env);
    printf("%s\n", result);

    return 0;
}