#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment *env, const char *request_name) {
    const char *template = env->name;
    size_t len = strlen(template) + strlen(request_name) + 10;
    char *rendered = malloc(len);
    snprintf(rendered, len, template, request_name);
    Response response = { .content = rendered };
    return response;
}

void home(Environment *env, const char *request_name) {
    Response response = render_response_from_env(env, request_name);
    printf("Response: %s\n", response.content);
    free((char *)response.content);
}