#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* request;
} Request;

typedef struct {
    const char* template;
} Environment;

typedef struct {
    const char* content;
} Response;

Response render_template(const char* template, const char* request) {
    // Simple rendering logic for demonstration purposes
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), "%s rendered with %s", template, request);
    return (Response){.content = buffer};
}

Response render_response_from_env(Environment env) {
    Request req = {.request = "Sample Request"};
    Response response = render_template(env.template, req.request);
    return response;
}

Response home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {.template = "Home Template"};
    Response response = home(env);
    printf("Response: %s\n", response.content);
    return 0;
}