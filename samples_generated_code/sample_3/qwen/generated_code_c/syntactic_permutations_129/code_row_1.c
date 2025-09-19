#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_TEMPLATE_LENGTH 500

char* get_name_from_request(const char* request) {
    const char* start = strstr(request, "name=");
    if (start == NULL) return "";
    start += strlen("name=");
    size_t length = strcspn(start, "& ");
    char* name = malloc(length + 1);
    strncpy(name, start, length);
    name[length] = '\0';
    return name;
}

char* get_template_from_env() {
    const char* template_str = getenv("TEMPLATE");
    if (template_str == NULL) return "";
    size_t length = strlen(template_str);
    char* template = malloc(length + 1);
    strcpy(template, template_str);
    return template;
}

char* render_template(const char* template, const char* name) {
    char* rendered_template = malloc(MAX_TEMPLATE_LENGTH);
    snprintf(rendered_template, MAX_TEMPLATE_LENGTH, template, name);
    return rendered_template;
}

char* render_response_from_env(const char* request, const char* env) {
    (void)env; // Assuming env is used to set environment variables elsewhere
    char* name = get_name_from_request(request);
    char* template = get_template_from_env();
    char* response = render_template(template, name);
    free(name);
    free(template);
    return response;
}

char* home(const char* request, const char* env) {
    return render_response_from_env(request, env);
}

int main() {
    // Example usage
    setenv("TEMPLATE", "Hello, %s!", 1);
    const char* request = "GET /?name=World HTTP/1.1";
    const char* env = "";
    char* response = home(request, env);
    printf("%s\n", response);
    free(response);
    return 0;
}