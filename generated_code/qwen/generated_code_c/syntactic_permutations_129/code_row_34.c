#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    char *template;
} Environment;

char* render_template(const char *template, const char *name) {
    // Simple template rendering logic
    size_t len = strlen(template) + strlen(name) + 1;
    char *rendered = (char *)malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

char* render_response_from_env(Environment *env, Request *request) {
    const char *template = env->template;
    const char *name = request->name;
    return render_template(template, name);
}

char* home(Environment *env) {
    // Assuming the request is available in some way, here we just create a mock one
    Request request = {"John Doe"};
    return render_response_from_env(env, &request);
}

int main() {
    Environment env = {"Hello, %s!"};
    char *response = home(&env);
    printf("%s\n", response);
    free(response); // Free the allocated memory for the rendered template
    return 0;
}