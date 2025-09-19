#include <stdio.h>
#include <string.h>

#define MAX_TEMPLATE_SIZE 1024

typedef struct {
    char *name;
} Environment;

const char* get_name_parameter(Environment *env) {
    return env->name ? env->name : "Guest";
}

const char* get_template(Environment *env) {
    // Simulating fetching a template from the environment.
    static const char defaultTemplate[] = 
        "<html><body>Welcome, <%s>!</body></html>";
    
    return defaultTemplate;
}

char* render_template(const char *template, const char *name) {
    char *rendered = (char *)malloc(MAX_TEMPLATE_SIZE);
    if (!rendered) return NULL;

    snprintf(rendered, MAX_TEMPLATE_SIZE, template, name);
    return rendered;
}

const char* render_response_from_env(Environment *env) {
    const char *name = get_name_parameter(env);
    const char *template = get_template(env);

    char *response = render_template(template, name);
    if (!response) response = "<html><body>Error rendering template.</body></html>";

    return response;
}

void home(Environment *env) {
    const char *response = render_response_from_env(env);
    printf("%s\n", response);
}

int main() {
    Environment env = { .name = "Alice" };
    
    home(&env);

    return 0;
}