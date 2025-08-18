#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content_type;
    const char *body;
} Response;

char* get_request_param(const char *key, const char *default_value) {
    // Simulate getting a request parameter (for simplicity, always return default value)
    return (char *)default_value;
}

Response render_response_from_env(Environment *env) {
    const char *name = get_request_param("name", "World");
    const char *template = env->name;
    size_t body_length = strlen(template) + strlen(name) + 20; // Extra space for formatting
    char *body = malloc(body_length);
    snprintf(body, body_length, template, name);

    Response response = {
        .content_type = "text/html",
        .body = body
    };
    return response;
}

Response home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "<h1>Hello, %s!</h1>" };
    Response response = home(&env);
    printf("Content-Type: %s\n", response.content_type);
    printf("Body: %s\n", response.body);
    free((void *)response.body); // Free allocated memory
    return 0;
}