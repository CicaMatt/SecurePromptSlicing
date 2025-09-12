#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
    const char *value;
} Parameter;

typedef struct {
    Parameter *parameters;
    int count;
} Request;

typedef struct {
    Request *request;
    const char **templates;
    int template_count;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment *env) {
    const char *name = NULL;
    for (int i = 0; i < env->request->count; i++) {
        if (strcmp(env->request->parameters[i].key, "name") == 0) {
            name = env->request->parameters[i].value;
            break;
        }
    }

    const char *template = env->templates[0]; // Assuming the first template is the one to use
    size_t content_length = strlen(template) + (name ? strlen(name) : 0) + 1;
    char *rendered_content = malloc(content_length);
    snprintf(rendered_content, content_length, template, name);

    Response response = { .content = rendered_content };
    return response;
}

Response home(Environment *env) {
    return render_response_from_env(env);
}