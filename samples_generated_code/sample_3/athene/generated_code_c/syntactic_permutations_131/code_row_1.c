#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *template;
} Env;

typedef struct {
    char *data;
} Request;

typedef struct {
    char *response;
} Response;

Response render_response_from_env(Env *env, Request *request) {
    char *template = env->template;
    char *rendered_template = malloc(strlen(template) + strlen(request->data) + 1);
    sprintf(rendered_template, template, request->data);
    Response response = { .response = rendered_template };
    return response;
}

Response home(Env *env) {
    Request request = { .data = "user input" };
    return render_response_from_env(env, &request);
}

int main() {
    Env env = { .template = "Hello, %s!" };
    Response response = home(&env);
    printf("%s\n", response.response);
    free(response.response);
    return 0;
}