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

const char* get_request_parameter(const char *key, const char *default_value) {
    // Dummy implementation for demonstration
    return getenv(key) ? getenv(key) : default_value;
}

Response render_response_from_env(Environment *env) {
    const char *name = get_request_parameter("name", "World");
    const char *template = env->name;
    size_t body_len = strlen(template) + strlen(name) + 10; // Extra space for formatting
    char *body = malloc(body_len);
    snprintf(body, body_len, template, name);
    Response response = { .content_type = "text/html", .body = body };
    return response;
}

Response home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "Hello %s!" };
    Response res = home(&env);
    printf("Content-Type: %s\n\n%s\n", res.content_type, res.body);
    free((void *)res.body); // Free the allocated memory
    return 0;
}