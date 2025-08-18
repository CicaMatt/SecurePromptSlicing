#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *name;
} Env;

typedef struct {
    const char *content_type;
    const char *body;
} Response;

Response render_response_from_env(Env *env) {
    const char *template = "<html><body>Hello, %s!</body></html>";
    size_t len = strlen(template) + strlen(env->name);
    char *rendered = malloc(len);
    snprintf(rendered, len, template, env->name);
    Response response = {"text/html", rendered};
    return response;
}

Response home(Env *env) {
    return render_response_from_env(env);
}