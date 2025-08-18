#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENV_SIZE 256
#define TEMPLATE_SIZE 1024

typedef struct {
    char name[50];
} Environment;

char* get_name_parameter(Environment *env) {
    // Simulating getting the name parameter from environment
    return env->name;
}

char* render_template(const char *template_str, const char *name) {
    static char rendered_template[TEMPLATE_SIZE];
    snprintf(rendered_template, TEMPLATE_SIZE, "Hello, %s! Welcome to your template: %s", name, template_str);
    return rendered_template;
}

char* render_response_from_env(Environment *env) {
    const char *template = "<html><body>This is a sample template.</body></html>";
    const char *name = get_name_parameter(env);

    char *rendered = render_template(template, name);
    
    static char response[TEMPLATE_SIZE];
    snprintf(response, TEMPLATE_SIZE, "HTTP/1.1 200 OK\nContent-Type: text/html\n\n%s", rendered);
    
    return response;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"John Doe"};
    char *response = home(&env);
    printf("%s\n", response);

    return 0;
}