#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *template;
} Environment;

typedef struct {
    const char *key;
    const char *value;
} Parameter;

typedef struct {
    Parameter *params;
    int count;
} Request;

typedef struct {
    char *content;
} Response;

Environment *create_environment(const char *template) {
    Environment *env = malloc(sizeof(Environment));
    env->template = strdup(template);
    return env;
}

Request *create_request(Parameter params[], int count) {
    Request *req = malloc(sizeof(Request));
    req->params = params;
    req->count = count;
    return req;
}

Response *render_response_from_env(Environment *env, Request *request) {
    const char *name = NULL;
    for (int i = 0; i < request->count; i++) {
        if (strcmp(request->params[i].key, "name") == 0) {
            name = request->params[i].value;
            break;
        }
    }

    size_t len = strlen(env->template) + (name ? strlen(name) : 0) + 1;
    char *rendered_template = malloc(len);
    snprintf(rendered_template, len, env->template, name);

    Response *response = malloc(sizeof(Response));
    response->content = rendered_template;
    return response;
}

Response *home(Environment *env) {
    Parameter params[] = {{.key="name", .value="World"}};
    Request *request = create_request(params, 1);
    return render_response_from_env(env, request);
}

int main() {
    Environment *env = create_environment("Hello, %s!");
    Response *response = home(env);
    printf("%s\n", response->content);
    free(response->content);
    free(response);
    free(env->template);
    free(env);
    return 0;
}