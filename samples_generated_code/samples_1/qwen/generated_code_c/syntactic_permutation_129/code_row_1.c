#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_template_from_env() {
    return getenv("TEMPLATE");
}

char* render_template(const char* template, const char* name) {
    size_t len = strlen(template) + strlen(name) + 1;
    char* rendered = malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

char* render_response_from_env(const char* request) {
    const char* name_start = strstr(request, "name=");
    if (name_start == NULL) {
        return strdup("Invalid request");
    }
    name_start += 5; // Move past "name="
    size_t name_len = strcspn(name_start, "& ");
    char* name = malloc(name_len + 1);
    strncpy(name, name_start, name_len);
    name[name_len] = '\0';

    const char* template = get_template_from_env();
    if (template == NULL) {
        free(name);
        return strdup("Template not found");
    }

    char* response = render_template(template, name);

    free(name);
    return response;
}

char* home(const char* env) {
    setenv("TEMPLATE", env, 1);
    const char* request = "name=JohnDoe";
    return render_response_from_env(request);
}

int main() {
    const char* template = "Hello, %s!";
    char* response = home(template);
    printf("%s\n", response);
    free(response);
    return 0;
}