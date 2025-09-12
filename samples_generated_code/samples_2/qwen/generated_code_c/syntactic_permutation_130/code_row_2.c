#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_TEMPLATE_SIZE 1024

char* get_parameter(const char* request, const char* param_name) {
    char search_str[64];
    snprintf(search_str, sizeof(search_str), "%s=", param_name);
    char* pos = strstr(request, search_str);
    if (pos == NULL) return NULL;
    pos += strlen(search_str);
    char* end_pos = strchr(pos, '&');
    int length = end_pos ? (end_pos - pos) : strlen(pos);
    char* result = malloc(length + 1);
    strncpy(result, pos, length);
    result[length] = '\0';
    return result;
}

char* get_template_from_env() {
    const char* template_str = getenv("TEMPLATE");
    if (!template_str) return NULL;
    size_t len = strlen(template_str);
    char* template_copy = malloc(len + 1);
    strcpy(template_copy, template_str);
    return template_copy;
}

char* render_response_from_env(const char* request) {
    char* name = get_parameter(request, "name");
    if (!name) return strdup("Name parameter not found");

    char* template = get_template_from_env();
    if (!template) {
        free(name);
        return strdup("Template not found in environment");
    }

    char response[MAX_TEMPLATE_SIZE];
    snprintf(response, sizeof(response), template, name);

    free(name);
    free(template);
    char* response_copy = malloc(strlen(response) + 1);
    strcpy(response_copy, response);
    return response_copy;
}

char* home(const char* env) {
    setenv("TEMPLATE", "%s's home page", 1);
    return render_response_from_env(env);
}

int main() {
    const char* request = "name=JohnDoe&age=30";
    char* response = home(request);
    printf("%s\n", response);
    free(response);
    return 0;
}