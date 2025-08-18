#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_parameter(const char* env, const char* param_name) {
    char param[256];
    snprintf(param, sizeof(param), "%s=", param_name);
    char* pos = strstr(env, param);
    if (pos == NULL) return NULL;
    char* value_start = pos + strlen(param);
    char* value_end = strchr(value_start, '&');
    int value_len = value_end ? value_end - value_start : strlen(value_start);
    char* value = malloc((value_len + 1) * sizeof(char));
    strncpy(value, value_start, value_len);
    value[value_len] = '\0';
    return value;
}

char* render_response_from_env(const char* env) {
    char* name = get_parameter(env, "name");
    if (name == NULL) return strdup("Name not provided");
    char response[256];
    snprintf(response, sizeof(response), "Hello, %s!", name);
    free(name);
    return strdup(response);
}

char* home(const char* env) {
    return render_response_from_env(env);
}

int main() {
    const char* env = "name=Alice&age=30";
    char* response = home(env);
    printf("%s\n", response);
    free(response);
    return 0;
}