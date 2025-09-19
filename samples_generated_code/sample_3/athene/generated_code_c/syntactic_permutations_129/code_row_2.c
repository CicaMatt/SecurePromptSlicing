#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
    const char *template;
} Environment;

typedef struct {
    const char *body;
} Response;

Response render_response_from_env(Environment *env) {
    const char *name = getenv("HTTP_NAME"); // Assuming this is how the name parameter is passed in the environment
    if (name == NULL) name = "World";
    
    size_t len = strlen(env->template) + strlen(name) + 10;
    char *rendered = malloc(len);
    snprintf(rendered, len, env->template, name);

    Response response = {.body = rendered};
    return response;
}

void home(Environment *env) {
    Response resp = render_response_from_env(env);
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n%s\n", resp.body);
    free((char *)resp.body); // Free the allocated memory for the rendered template
}