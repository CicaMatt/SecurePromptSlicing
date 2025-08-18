#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
    const char *template;
} Environment;

char* render_template(const char* template, const char* name) {
    size_t len = strlen(template) + strlen(name) + 1;
    char* rendered = (char*)malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

const char* get_name_parameter(Environment *env) {
    // For the purpose of this example, we assume "Alice" as a static user request parameter
    return "Alice";
}

const char* get_template_from_env(Environment *env) {
    return env->template;
}

const char* render_response_from_env(Environment *env) {
    const char* name = get_name_parameter(env);
    const char* template = get_template_from_env(env);
    return render_template(template, name);
}

void home() {
    Environment env = { .name = "Home", .template = "Hello, %s! Welcome to the homepage." };
    const char *response = render_response_from_env(&env);
    printf("%s\n", response);
    free((void*)response); // Freeing memory allocated by render_template
}

int main() {
    home();
    return 0;
}