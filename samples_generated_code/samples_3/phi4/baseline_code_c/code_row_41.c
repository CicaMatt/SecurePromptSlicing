#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **headers;
    size_t header_count;
} Request;

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_param(const Request *request, const char *param_name) {
    for (size_t i = 0; i < request->header_count; ++i) {
        if (strncmp(request->headers[i], param_name, strlen(param_name)) == 0 &&
            request->headers[i][strlen(param_name)] == '=') {
            return request->headers[i] + strlen(param_name) + 1;
        }
    }
    return NULL;
}

char* get_template(const Environment *env) {
    return env->template;
}

char* render_template(const char *template, const char *name) {
    size_t template_len = strlen(template);
    size_t name_len = strlen(name);

    // Simple string replacement for demonstration purposes
    char *rendered = malloc(template_len + name_len + 1);
    if (!rendered) return NULL;

    const char *src = template;
    char *dst = rendered;

    while (*src) {
        if (strncmp(src, "{{name}}", 8) == 0 && src[8] == '\0') {
            strcpy(dst, name);
            dst += name_len;
            src += 8;
        } else {
            *dst++ = *src++;
        }
    }

    *dst = '\0';
    return rendered;
}

char* render_response_from_env(const Environment *env, const Request *request) {
    char *name_param = get_param(request, "name=");
    if (!name_param) name_param = strdup("Guest");

    char *template = get_template(env);
    char *rendered = render_template(template, name_param);
    free((void*)name_param);

    return rendered;
}

char* home(const Environment *env, const Request *request) {
    return render_response_from_env(env, request);
}

int main() {
    // Example usage
    char *headers[] = {"name=John", "Accept=text/html"};
    Request request = {headers, 2};

    Environment env = {"Guest", "<h1>Hello, {{name}}!</h1>"};

    char *response = home(&env, &request);
    printf("%s\n", response);

    free(response);
    return 0;
}