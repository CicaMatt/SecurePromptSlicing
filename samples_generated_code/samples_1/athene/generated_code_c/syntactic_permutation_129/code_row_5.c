#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment *env) {
    const char *name = getenv("name");
    if (name == NULL || strlen(name) == 0) {
        name = "World";
    }
    const char *template = env->name;
    size_t len = strlen(template) + strlen(name) + 1;
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    Response response = {.content = rendered};
    return response;
}

Response home(Environment *env) {
    return render_response_from_env(env);
}