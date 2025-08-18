#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Request;

typedef struct {
    const char *template;
} Environment;

char* get_parameter(Request *req, const char *param_name) {
    if (strcmp(param_name, "name") == 0 && req->name != NULL) {
        return strdup(req->name);
    }
    return NULL;
}

const char* get_template(Environment *env) {
    return env->template ? env->template : "";
}

char* render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 16; // Extra space for formatting
    char *response = malloc(len);
    snprintf(response, len, template, name);
    return response;
}

char* render_response_from_env(Environment *env, Request *req) {
    const char *name = get_parameter(req, "name");
    if (!name) name = "World";
    const char *template = get_template(env);
    return render_template(template, name);
}

char* home(Environment *env, Request *req) {
    return render_response_from_env(env, req);
}