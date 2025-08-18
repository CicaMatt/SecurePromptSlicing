#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *template;
} Response;

Response *render_response_from_env(Environment *env) {
    const char *name = getenv("USER_NAME"); // Assuming USER_NAME is the environment variable for name
    if (name == NULL) name = "Guest";

    const char *template = env->name; // Assuming env->name holds the template string

    size_t len = strlen(template) + strlen(name) + 1;
    char *rendered_template = malloc(len);
    snprintf(rendered_template, len, template, name);

    Response *response = malloc(sizeof(Response));
    response->template = rendered_template;

    return response;
}

void home(Environment *env) {
    Response *response = render_response_from_env(env);
    printf("Response: %s\n", response->template);
    free((char *)response->template);
    free(response);
}