#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *request;
} Environment;

char* get_request_name(const char *request) {
    if (strstr(request, "name=")) {
        return strdup(strchr(strstr(request, "name="), '=') + 1);
    }
    return NULL;
}

char* render_template(const char *template_name) {
    // Simulate template rendering based on the name
    char *buffer = malloc(256);
    snprintf(buffer, 256, "<html><body><h1>Hello from template: %s</h1></body></html>", template_name ? template_name : "default");
    return buffer;
}

char* render_response_from_env(const Environment *env) {
    const char *request = env->request;
    const char *name = get_request_name(request);
    char *template_content = render_template(name);
    free((void *)name);  // Free the memory allocated by strdup
    char *response = malloc(strlen(template_content) + 100);
    snprintf(response, strlen(template_content) + 100, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", template_content);
    free((void *)template_content);  // Free the rendered content
    return response;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .request = "GET /home?name=example" };
    char *response = home(&env);
    printf("%s", response);
    free(response);  // Free the allocated memory for the response
    return 0;
}