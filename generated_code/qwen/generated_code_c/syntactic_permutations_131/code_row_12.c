#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
} Request;

typedef struct {
    char* template;
} Environment;

typedef struct {
    char* content;
} Response;

Response render_template(const char* template, const char* name) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), template, name);
    Response response = { .content = strdup(buffer) };
    return response;
}

char* get_template(Environment* env) {
    return env->template;
}

char* get_name(Request* request) {
    return request->name;
}

Response render_response_from_env(Environment* env, Request* request) {
    char* template = get_template(env);
    char* name = get_name(request);
    Response response = render_template(template, name);
    return response;
}

Response home(Environment* env, Request* request) {
    return render_response_from_env(env, request);
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Request request = { .name = "World" };

    Response response = home(&env, &request);
    printf("%s\n", response.content);
    free(response.content);

    return 0;
}