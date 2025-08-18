#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENV_SIZE 1000

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_request_parameter(const char *param, const char *request) {
    char *start = strstr(request, param);
    if (!start || start == request) return NULL;
    
    start += strlen(param); // Move to the end of parameter name
    while (*start == ' ') start++; // Skip spaces

    char *end = strchr(start, '&');
    if (end) {
        size_t len = end - start;
        char *value = malloc(len + 1);
        strncpy(value, start, len);
        value[len] = '\0';
        return value;
    }

    char *last = strrchr(request, ' ');
    if (!last || last == request) return strdup(start);

    size_t len = last - start;
    char *value = malloc(len + 1);
    strncpy(value, start, len);
    value[len] = '\0';
    return value;
}

char* render_template(const char *template_str, const char *name) {
    if (!template_str || !name) return strdup("");

    size_t template_len = strlen(template_str);
    size_t name_len = strlen(name);

    // Allocate space for new string with placeholder replaced
    char *result = malloc(template_len + name_len + 1);
    char *current_pos = result;

    while (*template_str) {
        if (strncmp(template_str, "{{name}}", 8) == 0) {
            strcpy(current_pos, name);
            current_pos += name_len;
            template_str += 8; // Move past the placeholder
        } else {
            *current_pos++ = *template_str++;
        }
    }

    *current_pos = '\0';
    return result;
}

char* render_response_from_env(Environment env) {
    char *request = "name=John&other=value"; // Example request string

    char *user_name = get_request_parameter("name", request);
    
    if (!user_name || !env.name || !env.template) {
        free(user_name);
        return strdup("Invalid environment or parameters");
    }

    char *rendered_template = render_template(env.template, user_name);

    free(user_name);
    return rendered_template;
}

char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { "name", "Hello {{name}}!" };

    char *response = home(env);

    printf("Response: %s\n", response);

    free(response);

    return 0;
}