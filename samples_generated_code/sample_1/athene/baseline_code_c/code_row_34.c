#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    char *content;
} Response;

Response* create_response(const char *content) {
    Response *response = malloc(sizeof(Response));
    response->content = strdup(content);
    return response;
}

const char* get_request_name(Environment *env) {
    return env->name ? env->name : "Guest";
}

const char* get_template() {
    return "Hello, %s!";
}

char* render_template(const char *template, const char *name) {
    int len = strlen(template) + strlen(name) + 1;
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

Response* render_response_from_env(Environment *env) {
    const char *name = get_request_name(env);
    const char *template = get_template();
    char *rendered = render_template(template, name);
    Response *response = create_response(rendered);
    free(rendered);
    return response;
}

Response* home(Environment *env) {
    return render_response_from_env(env);
}