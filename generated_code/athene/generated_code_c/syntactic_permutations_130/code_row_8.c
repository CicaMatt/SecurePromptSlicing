#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Request;

typedef struct {
    Request *request;
    const char *template;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment *env) {
    const char *name = env->request->name;
    const char *template = env->template;
    size_t len = strlen(template) + strlen(name) + 10; // Extra space for formatting
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    Response response = { .content = rendered };
    return response;
}

Response home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Request request = { .name = "World" };
    Environment env = { .request = &request, .template = "Hello, %s!" };
    Response response = home(&env);
    printf("%s\n", response.content);
    free((void *)response.content);
    return 0;
}