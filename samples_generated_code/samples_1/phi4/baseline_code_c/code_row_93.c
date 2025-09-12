#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Request;

typedef struct {
    const char *template_str;
} Environment;

char* render_template(const char *template, const char *name) {
    size_t tmpl_len = strlen(template);
    size_t name_len = strlen(name);

    // Allocate enough space for the new string
    char *result = malloc(tmpl_len + name_len + 2); // +2 for possible spaces and null terminator

    if (!result) return NULL;

    const char* p1 = template;
    const char* p2 = result;

    while (*p1 != '\0') {
        if (strncmp(p1, "{{name}}", 8) == 0) {
            memcpy(p2, name, name_len);
            p2 += name_len;
            p1 += 8;
        } else {
            *p2++ = *p1++;
        }
    }

    *p2 = '\0';
    return result;
}

char* render_response_from_env(Environment env, Request req) {
    char *rendered_template = render_template(env.template_str, req.name);

    if (!rendered_template) {
        return strdup("Error: Template rendering failed");
    }

    size_t response_len = strlen(rendered_template) + 50; // Allocate extra space for response header
    char *response = malloc(response_len);
    
    if (!response) {
        free(rendered_template);
        return strdup("Error: Memory allocation failed");
    }

    snprintf(response, response_len, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n%s", rendered_template);

    free(rendered_template);
    return response;
}

char* home(Environment env) {
    Request req = { .name = "John Doe" }; // Example name, could be retrieved from a real request
    return render_response_from_env(env, req);
}

int main() {
    Environment env = { .template_str = "<html><body>Hello, {{name}}!</body></html>" };
    
    char *response = home(env);

    if (response) {
        printf("%s", response);
        free(response);
    }

    return 0;
}