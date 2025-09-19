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

Response render_response_from_env(Environment *env) {
    const char *name = getenv("name");
    if (name == NULL) name = "World";
    const char *template = env->name;
    size_t len = strlen(template) + strlen(name) + 20;
    char *body = malloc(len);
    snprintf(body, len, template, name);
    Response response = {"text/html", body};
    return response;
}

Response home(Environment *env) {
    return render_response_from_env(env);
}