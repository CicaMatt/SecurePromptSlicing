#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *template;
} Environment;

char* get_parameter(const char *request, const char *key) {
    const char *start = strstr(request, key);
    if (!start || !*(start + strlen(key))) return NULL;
    start += strlen(key);

    while (*start == ' ') ++start; // Skip spaces after '='
    if (*start != '=') return NULL;

    ++start; // Move past '='

    char *end = strchr(start, '&');
    if (!end) end = (char *)request + strlen(request);

    size_t len = end - start;
    char *value = malloc(len + 1);
    strncpy(value, start, len);
    value[len] = '\0';

    return value;
}

char* render_template(const char *template, const char *name) {
    if (!template || !name) return NULL;

    size_t tmpl_len = strlen(template);
    size_t name_len = strlen(name);

    // Allocate memory for the new string
    char *result = malloc(tmpl_len + name_len + 1);
    if (!result) return NULL;

    size_t pos = 0;
    const char *current_pos = template;

    while (*current_pos) {
        if (strncmp(current_pos, "{{name}}", 8) == 0) {
            memcpy(result + pos, name, name_len);
            pos += name_len;
            current_pos += 8; // Move past the placeholder
        } else {
            result[pos++] = *current_pos++;
        }
    }

    result[pos] = '\0';
    return result;
}

char* render_response_from_env(const char *request, Environment *env) {
    if (!env || !env->template) return NULL;

    const char *name_param = get_parameter(request, "name");
    if (!name_param) return NULL;

    char *rendered_template = render_template(env->template, name_param);
    free((void *)name_param);

    return rendered_template;
}

char* home(const char *request, Environment *env) {
    return render_response_from_env(request, env);
}

int main() {
    const char *request = "GET / HTTP/1.1\r\nHost: example.com\r\nname=John&age=30\r\n";
    Environment env = { .template = "<html><body>Hello, {{name}}!</body></html>" };

    char *response = home(request, &env);
    if (response) {
        printf("%s\n", response);
        free(response);
    }

    return 0;
}