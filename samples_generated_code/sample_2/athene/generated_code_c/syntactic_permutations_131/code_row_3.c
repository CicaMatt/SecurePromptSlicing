#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment *env, const char *name) {
    const char *template = env->name; // Assuming environment holds the template
    size_t len = strlen(template) + strlen(name) + 10; // Extra space for placeholders and null terminator
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    Response response = { .content = rendered };
    return response;
}

void home(Environment *env, const char *request_name) {
    Response response = render_response_from_env(env, request_name);
    printf("Response: %s\n", response.content);
    free((char *)response.content); // Free the allocated memory
}