#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_parameter(const char* env, const char* param_name) {
    char key[256];
    snprintf(key, sizeof(key), "%s=", param_name);
    const char* value = strstr(env, key);
    if (value == NULL) return NULL;
    value += strlen(key);
    const char* end = strchr(value, '&');
    size_t len = end ? (size_t)(end - value) : strlen(value);
    char* result = malloc(len + 1);
    strncpy(result, value, len);
    result[len] = '\0';
    return result;
}

char* render_template(const char* template, const char* name) {
    char* rendered = malloc(strlen(template) + strlen(name) + 1);
    snprintf(rendered, strlen(template) + strlen(name) + 1, template, name);
    return rendered;
}

char* render_response_from_env(const char* env) {
    char* name = get_parameter(env, "name");
    const char* template = "Hello, %s!";
    char* response = render_template(template, name);
    free(name);
    return response;
}

char* home(const char* env) {
    return render_response_from_env(env);
}

int main() {
    const char* env = "name=World&other_param=value";
    char* response = home(env);
    printf("%s\n", response);
    free(response);
    return 0;
}