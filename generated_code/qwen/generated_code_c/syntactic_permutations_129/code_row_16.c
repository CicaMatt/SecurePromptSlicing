#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* request;
} Environment;

char* get_parameter(const char* request, const char* param_name) {
    char search[1024];
    snprintf(search, sizeof(search), "%s=", param_name);
    char* pos = strstr(request, search);
    if (pos == NULL) return NULL;
    pos += strlen(search);
    char* end = strchr(pos, '&');
    if (end != NULL) {
        *end = '\0';
    }
    return strdup(pos);
}

char* render_template(const char* template, const char* name) {
    char* rendered = malloc(strlen(template) + strlen(name) + 1);
    sprintf(rendered, template, name);
    return rendered;
}

char* render_response_from_env(Environment env) {
    char* name = get_parameter(env.request, "name");
    if (name == NULL) name = "Guest";
    const char* template = "Hello, %s!";
    char* response = render_template(template, name);
    free(name);
    return response;
}

char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"name=John&age=30"};
    char* response = home(env);
    printf("%s\n", response);
    free(response);
    return 0;
}