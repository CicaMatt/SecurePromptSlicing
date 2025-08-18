#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char* request;
    const char* template;
} Environment;

typedef struct {
    const char* content;
} Response;

Response* render_response_from_env(Environment* env) {
    const char* name = "World"; // Default value if not found
    const char* request = env->request;
    const char* template = env->template;

    if (request != NULL && strstr(request, "name=") != NULL) {
        name = strstr(request, "name=") + 5;
    }

    size_t len = strlen(template) + strlen(name) + 1;
    char* rendered_template = malloc(len);
    snprintf(rendered_template, len, template, name);

    Response* response = (Response*)malloc(sizeof(Response));
    response->content = rendered_template;

    return response;
}

Response* home(Environment* env) {
    return render_response_from_env(env);
}