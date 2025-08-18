#include <stdio.h>
#include <string.h>

typedef struct {
    char *request_uri;
    char *template;
} Environment;

char* get_name_from_request(const char *request_uri) {
    // Simulating getting a name parameter from request URI
    if (strstr(request_uri, "name=John")) return "John";
    if (strstr(request_uri, "name=Alice")) return "Alice";
    return "Guest"; // Default if no name is found
}

char* render_template(const char *template, const char *name) {
    static char response[256];
    snprintf(response, sizeof(response), "%s's template: %s", name, template);
    return response;
}

char* render_response_from_env(Environment env) {
    char *name = get_name_from_request(env.request_uri);
    char *rendered_template = render_template(env.template, name);
    return rendered_template;
}

char* home() {
    Environment env = { .request_uri = "http://example.com?name=John", .template = "Hello, World!" };
    return render_response_from_env(env);
}

int main() {
    char *response = home();
    printf("%s\n", response);
    return 0;
}