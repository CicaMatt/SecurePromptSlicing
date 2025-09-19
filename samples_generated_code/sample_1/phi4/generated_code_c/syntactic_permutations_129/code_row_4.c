#include <stdio.h>
#include <string.h>

#define MAX_ENV_SIZE 256
#define MAX_TEMPLATE_SIZE 1024

typedef struct {
    char name[MAX_ENV_SIZE];
    char template[MAX_TEMPLATE_SIZE];
} Environment;

char* render_template(const char *template, const char *name) {
    static char rendered[MAX_TEMPLATE_SIZE * 2]; // Assuming the result won't exceed twice the template size
    snprintf(rendered, sizeof(rendered), template, name);
    return rendered;
}

char* get_name_from_request(Environment env) {
    // Simulate getting a name parameter from request for demonstration purposes.
    // In actual use, this would involve parsing HTTP headers or query parameters.
    strcpy(env.name, "John Doe");
    return env.name;
}

char* get_template_from_env(Environment env) {
    // Simulate retrieving a template from environment. In real scenarios, this could be fetched from files or databases
    snprintf(env.template, sizeof(env.template), "Hello, %s!");
    return env.template;
}

char* render_response_from_env(Environment env) {
    char *name = get_name_from_request(env);
    char *template = get_template_from_env(env);
    return render_template(template, name);
}

void home() {
    Environment env;
    char *response = render_response_from_env(env);
    printf("Response: %s\n", response);
}

int main() {
    home();
    return 0;
}