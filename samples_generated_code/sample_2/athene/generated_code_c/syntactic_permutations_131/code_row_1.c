#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *template;
} Environment;

typedef struct {
    const char *data;
} Request;

typedef struct {
    const char *content;
} Response;

Response* render_response_from_env(Environment *env, Request *request) {
    const char *template = env->template;
    const char *request_data = request->data;
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), template, request_data);
    Response *response = (Response *)malloc(sizeof(Response));
    response->content = strdup(buffer);
    return response;
}

Response* home(Environment *env) {
    Request request = { .data = "user input" };
    return render_response_from_env(env, &request);
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Response *response = home(&env);
    printf("%s\n", response->content);
    free((void *)response->content);
    free(response);
    return 0;
}