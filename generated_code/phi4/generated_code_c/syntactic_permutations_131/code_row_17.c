#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    char *template;
} Environment;

const char* get_template_name(const Request *request) {
    return request->name ? request->name : "default";
}

char* render_template(const char *template_name, const char *param) {
    // Simple template rendering logic
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), "Rendering template: %s with param: %s", template_name, param);
    return buffer;
}

const char* render_response_from_env(Environment *env, Request *request) {
    const char *template_name = get_template_name(request);
    return render_template(template_name, env->template);
}

const char* home(Environment *env) {
    Request request = { .name = "example" };
    return render_response_from_env(env, &request);
}

int main() {
    Environment env = { .template = "example_param" };
    const char *response = home(&env);
    printf("%s\n", response);
    return 0;
}