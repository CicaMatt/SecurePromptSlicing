#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *request;
    char *template;
} Environment;

typedef struct {
    char *content;
} Response;

Response* render_response_from_env(Environment *env) {
    char *request = env->request;
    char *template = env->template;
    size_t len = strlen(template) + strlen(request) + 1;
    char *rendered = malloc(len);
    snprintf(rendered, len, template, request);
    Response *response = malloc(sizeof(Response));
    response->content = rendered;
    return response;
}

Response* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"user_request", "Template: %s"};
    Response *resp = home(&env);
    printf("Response: %s\n", resp->content);
    free(resp->content);
    free(resp);
    return 0;
}