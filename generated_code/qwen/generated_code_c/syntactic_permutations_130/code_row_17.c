#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    Request *request;
} Environment;

typedef struct {
    char *body;
} Response;

Response* create_response(const char *template, const char *name) {
    Response *response = (Response*)malloc(sizeof(Response));
    response->body = (char*)malloc(strlen(template) + strlen(name) + 1);
    sprintf(response->body, template, name);
    return response;
}

void free_response(Response *response) {
    free(response->body);
    free(response);
}

Response* render_response_from_env(Environment *env) {
    const char *template = "Hello, %s!";
    const char *name = env->request->name;
    return create_response(template, name);
}

Response* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Request request = {"Alice"};
    Environment env = {&request};

    Response *response = home(&env);
    printf("%s\n", response->body);

    free_response(response);
    return 0;
}