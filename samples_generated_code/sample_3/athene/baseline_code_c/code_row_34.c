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

const char* get_request_name(const char *request) {
    const char *name = "World";
    if (request && strstr(request, "?name=")) {
        name = request + strlen("?name=");
    }
    return name;
}

Response render_response_from_env(Environment env, const char *request) {
    const char *name = get_request_name(request);
    const char *template = env.name;
    char body[256];
    snprintf(body, sizeof(body), "Hello, %s! This is the template: %s", name, template);
    return (Response){.content_type = "text/html", .body = strdup(body)};
}

Response home(Environment env, const char *request) {
    Response response = render_response_from_env(env, request);
    return response;
}