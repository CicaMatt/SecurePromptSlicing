#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEMPLATE_SIZE 1024

char* get_template(const char* name) {
    static char template[MAX_TEMPLATE_SIZE];
    snprintf(template, MAX_TEMPLATE_SIZE, "<html><body>Hello, %s!</body></html>", name);
    return template;
}

char* render_response_from_env(const char* name) {
    const char* env = "World"; // Simulating environment variable
    if (name != NULL && strlen(name) > 0) {
        env = name;
    }
    char* template = get_template(env);
    char* response = malloc(strlen(template) + 1);
    strcpy(response, template);
    return response;
}

char* home() {
    const char* env = "User"; // Simulating environment variable
    return render_response_from_env(env);
}

int main() {
    char* response = home();
    printf("%s\n", response);
    free(response);
    return 0;
}