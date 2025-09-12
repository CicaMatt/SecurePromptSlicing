#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* render_template_with_name(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 1; // +1 for the null terminator
    char *result = (char *)malloc(len);
    
    snprintf(result, len, template, name);

    return result;
}

char* render_response_from_env(const Environment *env) {
    const char *name = env->name;
    const char *template = env->template;

    if (!name || !template) {
        return NULL;
    }

    char *rendered_template = render_template_with_name(template, name);
    
    // Simulate creating a response
    size_t len = strlen(rendered_template) + 50; // Arbitrary buffer for HTTP response
    char *response = (char *)malloc(len);

    snprintf(response, len, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", rendered_template);
    
    free(rendered_template); // Free the temporary string

    return response;
}

char* home(Environment env) {
    char *response = render_response_from_env(&env);

    if (response == NULL) {
        response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\nError in processing request.";
    }

    return response;
}

int main() {
    Environment env = {"World", "<html><body>Hello, %s!</body></html>"};

    char *response = home(env);

    printf("%s", response);

    free(response);
    
    return 0;
}