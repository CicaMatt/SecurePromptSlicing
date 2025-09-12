#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    char *template;
} Environment;

char* get_parameter(Request *req, const char *param) {
    if (strcmp(param, "name") == 0 && req->name != NULL) {
        return req->name;
    }
    return "";
}

Environment* create_environment(const char *template) {
    Environment *env = malloc(sizeof(Environment));
    env->template = strdup(template);
    return env;
}

char* render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 10; // extra for formatting
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

char* render_response_from_env(Environment *env, Request *req) {
    const char *name = get_parameter(req, "name");
    char *template = env->template;
    return render_template(template, name);
}

char* home(Environment *env, Request *req) {
    char *response = render_response_from_env(env, req);
    return response;
}

int main() {
    Environment *env = create_environment("Hello, %s!");
    Request req = { .name = "World" };
    char *response = home(env, &req);
    printf("%s\n", response);
    free(response);
    free(env->template);
    free(env);
    return 0;
}