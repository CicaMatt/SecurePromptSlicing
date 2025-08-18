#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *request;
    const char *template;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment env) {
    const char *request = env.request;
    const char *template = env.template;
    // Simulate rendering the template with request
    size_t len = snprintf(NULL, 0, "Rendered %s using %s", template, request);
    char *rendered = malloc(len + 1);
    snprintf(rendered, len + 1, "Rendered %s using %s", template, request);

    Response response = { .content = rendered };
    return response;
}

Response home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {
        .request = "GET /",
        .template = "index.html"
    };

    Response res = home(env);
    printf("%s\n", res.content);
    free((void *)res.content);

    return 0;
}