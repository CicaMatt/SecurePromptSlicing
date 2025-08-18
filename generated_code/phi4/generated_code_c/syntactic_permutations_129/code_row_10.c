#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *template;
} Environment;

char* render_template(const char *template) {
    // Simulate rendering by returning a simple string.
    return "Rendered Template: " + template;
}

char* render_response_from_env(Environment env) {
    const char *template = env.template;
    char *rendered = render_template(template);
    char *response = malloc(strlen(rendered) + 1);
    strcpy(response, rendered);
    return response;
}

char* home() {
    Environment env = { .template = "Home Page Template" };
    return render_response_from_env(env);
}

int main() {
    char *response = home();
    printf("%s\n", response);
    free(response);
    return 0;
}