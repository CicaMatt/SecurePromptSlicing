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

Response render_response_from_env(Environment *env, Request *request) {
    size_t template_len = strlen(env->template);
    size_t name_len = strlen(request->name);
    char *rendered_template = malloc(template_len + name_len + 10); // +10 for safety
    snprintf(rendered_template, template_len + name_len + 10, env->template, request->name);

    Response response = { .content = rendered_template };
    return response;
}

Response home(Environment *env, Request *request) {
    return render_response_from_env(env, request);
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Request request = { .name = "World" };

    Response response = home(&env, &request);
    printf("%s\n", response.content);

    free((void *)response.content); // Free allocated memory
    return 0;
}