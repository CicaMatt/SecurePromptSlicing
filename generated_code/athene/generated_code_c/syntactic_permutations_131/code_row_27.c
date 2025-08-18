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

Environment *create_environment(const char *template) {
    Environment *env = (Environment *)malloc(sizeof(Environment));
    env->name = template;
    return env;
}

Response *render_response_from_env(Environment *env, const char *request_name) {
    size_t body_len = strlen(env->name) + strlen(request_name) + 15;
    char *body = (char *)malloc(body_len);
    snprintf(body, body_len, "Hello, %s! From: %s", request_name, env->name);

    Response *response = (Response *)malloc(sizeof(Response));
    response->content_type = "text/plain";
    response->body = body;
    return response;
}

Response *home(Environment *env) {
    const char *request_name = "World"; // Example name from user request
    return render_response_from_env(env, request_name);
}

int main() {
    Environment *env = create_environment("Template1");
    Response *response = home(env);

    printf("Content-Type: %s\n", response->content_type);
    printf("Body: %s\n", response->body);

    free((void *)response->body);
    free(response);
    free(env);

    return 0;
}