#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *template;
} Environment;

typedef struct {
    char *request;
} UserRequest;

typedef struct {
    char *content;
} Response;

Response* create_response(const char *content) {
    Response *response = (Response *)malloc(sizeof(Response));
    response->content = strdup(content);
    return response;
}

void destroy_response(Response *response) {
    free(response->content);
    free(response);
}

Environment* create_environment(const char *template) {
    Environment *env = (Environment *)malloc(sizeof(Environment));
    env->template = strdup(template);
    return env;
}

void destroy_environment(Environment *env) {
    free(env->template);
    free(env);
}

UserRequest* create_user_request(const char *request) {
    UserRequest *user_request = (UserRequest *)malloc(sizeof(UserRequest));
    user_request->request = strdup(request);
    return user_request;
}

void destroy_user_request(UserRequest *user_request) {
    free(user_request->request);
    free(user_request);
}

char* render_template(const char *template, const char *request) {
    // Simple rendering logic for demonstration
    char *rendered = (char *)malloc(strlen(template) + strlen(request) + 1);
    sprintf(rendered, template, request);
    return rendered;
}

Response* render_response_from_env(Environment *env, UserRequest *user_request) {
    char *rendered_template = render_template(env->template, user_request->request);
    Response *response = create_response(rendered_template);
    free(rendered_template);
    return response;
}

Response* home(Environment *env, UserRequest *user_request) {
    return render_response_from_env(env, user_request);
}

int main() {
    Environment *env = create_environment("Hello, %s!");
    UserRequest *user_request = create_user_request("World");

    Response *response = home(env, user_request);

    printf("%s\n", response->content);

    destroy_response(response);
    destroy_user_request(user_request);
    destroy_environment(env);

    return 0;
}