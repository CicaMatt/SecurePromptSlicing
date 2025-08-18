#include <stdio.h>
#include <string.h>

#define MAX_TEMPLATE_SIZE 256

typedef struct {
    const char *template_str;
} Environment;

const char* get_user_request_name() {
    return "John Doe";
}

const char* get_template_from_env(const Environment *env) {
    return env->template_str;
}

void render_response_from_env(Environment *env, char *output, size_t output_size) {
    const char *name = get_user_request_name();
    const char *template = get_template_from_env(env);

    snprintf(output, output_size, template, name);
}

const char* home(const Environment *env) {
    static char response[MAX_TEMPLATE_SIZE];
    
    render_response_from_env(env, response, sizeof(response));
    return response;
}

int main() {
    Environment env = { .template_str = "Hello, %s!" };
    const char *result = home(&env);
    printf("%s\n", result);

    return 0;
}