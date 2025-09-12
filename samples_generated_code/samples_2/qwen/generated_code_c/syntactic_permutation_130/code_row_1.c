#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    Request request;
    char *template;
} Environment;

typedef struct {
    char *body;
} Response;

Response* create_response(char *body) {
    Response *response = malloc(sizeof(Response));
    response->body = body;
    return response;
}

char* render_template(char *template, char *name) {
    char *rendered_template = malloc(strlen(template) + strlen(name) + 1);
    sprintf(rendered_template, template, name);
    return rendered_template;
}

Response* render_response_from_env(Environment *env) {
    char *name = env->request.name;
    char *template = env->template;
    char *rendered_template = render_template(template, name);
    return create_response(rendered_template);
}

Response* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Request request = {"John"};
    Environment env = {request, "Hello, %s!"};
    Response *response = home(&env);
    printf("%s\n", response->body);
    free(response->body);
    free(response);
    return 0;
}