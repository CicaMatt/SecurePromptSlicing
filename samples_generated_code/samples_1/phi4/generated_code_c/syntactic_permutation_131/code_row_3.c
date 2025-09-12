#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
    const char* template_str;
} Environment;

const char* get_user_request_name() {
    // Simulated user request, normally this would come from HTTP headers or parameters
    return "John Doe";
}

char* render_template(const char* template_str, const char* name) {
    size_t len = snprintf(NULL, 0, template_str, name);
    char* result = (char*)malloc(len + 1);
    if (result) {
        snprintf(result, len + 1, template_str, name);
    }
    return result;
}

const char* render_response_from_env(const Environment* env) {
    const char* user_name = get_user_request_name();
    return render_template(env->template_str, user_name);
}

void home() {
    Environment env = {"", "Hello, %s! Welcome to the homepage."};
    const char* response = render_response_from_env(&env);
    printf("%s\n", response);
    free((char*)response);
}

int main() {
    home();
    return 0;
}