#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Request;

typedef struct {
    const char *template;
} Environment;

typedef struct {
    const char *content;
} Response;

Response* render_response_from_env(Request *request, Environment *env) {
    size_t name_len = strlen(request->name);
    size_t template_len = strlen(env->template);
    char *rendered_template = malloc(template_len + name_len + 10); // extra for safety
    snprintf(rendered_template, template_len + name_len + 10, env->template, request->name);
    Response *response = (Response *)malloc(sizeof(Response));
    response->content = rendered_template;
    return response;
}

Response* home(Environment *env) {
    Request request = { .name = "World" };
    return render_response_from_env(&request, env);
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Response *response = home(&env);
    printf("%s\n", response->content);
    free((void *)response->content);
    free(response);
    return 0;
}