#include <stdio.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content_type;
    const char *body;
} Response;

Response render_response_from_env(Environment env, const char *request_name) {
    const char *template = env.name;
    size_t len = strlen(template) + strlen(request_name) + 10;
    char *rendered = malloc(len);
    snprintf(rendered, len, template, request_name);

    Response response = { .content_type = "text/html", .body = rendered };
    return response;
}

Response home(Environment env) {
    const char *request_name = "John Doe"; // Example name from user request
    return render_response_from_env(env, request_name);
}

int main() {
    Environment env = { .name = "<html><body>Hello, %s!</body></html>" };
    Response response = home(env);

    printf("Content-Type: %s\n", response.content_type);
    printf("%s\n", response.body);

    free((void *)response.body); // Free allocated memory
    return 0;
}