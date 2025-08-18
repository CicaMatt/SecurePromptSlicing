#include <stdio.h>
#include <string.h>

typedef struct {
    const char *name;
} Request;

typedef struct {
    Request *request;
    const char *template;
} Environment;

const char* get_template(Environment *env) {
    return env->template;
}

const char* get_name(Request *req) {
    if (req == NULL) return "";
    return req->name;
}

char* render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 1;
    char *response = malloc(len);
    snprintf(response, len, template, name);
    return response;
}

char* render_response_from_env(Environment *env) {
    const char *name = get_name(env->request);
    const char *template = get_template(env);
    return render_template(template, name);
}

char* home(Environment *env) {
    return render_response_from_env(env);
}