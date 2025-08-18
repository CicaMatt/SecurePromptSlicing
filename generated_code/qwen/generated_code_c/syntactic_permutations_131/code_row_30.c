#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* template;
} Environment;

char* get_parameter(const char* request, const char* param) {
    char* start = strstr(request, param);
    if (start == NULL) return NULL;
    start += strlen(param) + 1; // Move past the parameter name and '='
    char* end = strchr(start, ' ');
    if (end == NULL) end = start + strlen(start); // In case it's the last parameter
    int len = end - start;
    char* result = malloc(len + 1);
    strncpy(result, start, len);
    result[len] = '\0';
    return result;
}

char* render_template(const char* template, const char* name) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), template, name);
    return strdup(buffer);
}

char* render_response_from_env(Environment* env, const char* request) {
    char* name = get_parameter(request, "name");
    if (name == NULL) return strdup("Name parameter not found");

    char* rendered_template = render_template(env->template, name);
    free(name);
    return rendered_template;
}

char* home(Environment* env, const char* request) {
    return render_response_from_env(env, request);
}

int main() {
    Environment env;
    env.template = "Hello, %s!";

    const char* request = "name=John";
    char* response = home(&env, request);

    printf("%s\n", response);
    free(response);

    return 0;
}