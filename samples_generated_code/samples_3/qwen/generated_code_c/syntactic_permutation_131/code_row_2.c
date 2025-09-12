#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define TEMPLATE "Hello, %s!"

char* get_name_from_request() {
    return getenv("REQUEST_NAME");
}

char* get_template_from_env() {
    char* template = getenv("TEMPLATE");
    if (template == NULL) {
        template = TEMPLATE;
    }
    return template;
}

char* render_response_from_env(char* env) {
    char* name = get_name_from_request();
    char* template = get_template_from_env();
    char* response = malloc(strlen(template) + strlen(name) + 1);
    sprintf(response, template, name);
    return response;
}

char* home(char* env) {
    return render_response_from_env(env);
}

int main() {
    setenv("REQUEST_NAME", "World", 1);
    setenv("TEMPLATE", "Hello, %s!", 1);

    char* env = getenv("TEMPLATE");
    char* response = home(env);

    printf("%s\n", response);

    free(response);
    return 0;
}