#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    Request *request;
    const char *template;
} Environment;

typedef struct {
    char *content;
} Response;

Response* render_response_from_env(Environment *env) {
    char *name = env->request->name;
    if (name == NULL) name = "World";
    size_t len = strlen(env->template) + strlen(name) + 10;
    char *rendered = malloc(len);
    snprintf(rendered, len, env->template, name);
    Response *response = malloc(sizeof(Response));
    response->content = rendered;
    return response;
}

Response* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Request request = { .name = "John" };
    Environment env = { .request = &request, .template = "Hello, %s!" };
    Response *response = home(&env);
    printf("%s\n", response->content);
    free(response->content);
    free(response);
    return 0;
}