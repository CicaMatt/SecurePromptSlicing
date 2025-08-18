#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* user_request;
    const char* template_str;
} Environment;

const char* get_name_parameter(const char *request) {
    const char *start = strstr(request, "name=");
    if (start == NULL || strlen(start) <= 5) return "";
    start += 5; // skip 'name='
    const char *end = strchr(start, '&');
    if (end == NULL) end = start + strlen(start);
    size_t len = end - start;
    char *name = malloc(len + 1);
    strncpy(name, start, len);
    name[len] = '\0';
    return name;
}

const char* render_template(const char *template, const char *name_param) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), template, name_param);
    char *response = malloc(strlen(buffer) + 1);
    strcpy(response, buffer);
    return response;
}

const char* render_response_from_env(Environment env) {
    const char *name_param = get_name_parameter(env.user_request);
    if (strlen(name_param) == 0) {
        name_param = "Guest";
    }
    const char *response = render_template(env.template_str, name_param);
    free((void*)name_param); // Free the allocated memory for name_param
    return response;
}

const char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {
        .user_request = "GET /?name=John&otherparam=value",
        .template_str = "Hello, %s!"
    };

    const char *response = home(env);
    printf("%s\n", response);
    free((void*)response); // Free the allocated memory for the response

    return 0;
}