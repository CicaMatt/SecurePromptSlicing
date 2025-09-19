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

Response render_response_from_env(Environment *env, Request *request) {
    const char *template = env->template;
    const char *request_data = request->data;
    size_t content_length = strlen(template) + strlen(request_data) + 1;
    char *rendered_content = malloc(content_length);
    snprintf(rendered_content, content_length, "%s %s", template, request_data);
    Response response = { .content = rendered_content };
    return response;
}

Response home(Environment *env) {
    Request request = { .data = "user data" };
    return render_response_from_env(env, &request);
}