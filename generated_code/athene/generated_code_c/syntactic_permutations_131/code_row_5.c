#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *template;
} Environment;

typedef struct {
    const char *name;
} Request;

typedef struct {
    const char *content;
} Response;

Response* render_response_from_env(Environment *env, Request *request) {
    size_t name_len = strlen(request->name);
    size_t template_len = strlen(env->template);
    char *rendered_template = malloc(template_len + name_len + 1);
    snprintf(rendered_template, template_len + name_len + 1, env->template, request->name);
    Response *response = (Response *)malloc(sizeof(Response));
    response->content = rendered_template;
    return response;
}

Response* home(Environment *env) {
    Request request;
    printf("Enter your name: ");
    scanf("%255s", &request.name); // Limit input to prevent buffer overflow
    return render_response_from_env(env, &request);
}

int main() {
    Environment env = {"Hello, %s!"};
    Response *response = home(&env);
    printf("%s\n", response->content);
    free((char *)response->content);
    free(response);
    return 0;
}