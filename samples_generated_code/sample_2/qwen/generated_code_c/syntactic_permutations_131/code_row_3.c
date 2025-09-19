#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
} Request;

typedef struct {
    char* template;
} Environment;

char* get_name_parameter(const Request* request) {
    return request->name;
}

char* render_template(const char* template, const char* name) {
    static char response[256];
    snprintf(response, sizeof(response), template, name);
    return response;
}

char* render_response_from_env(Environment* env, Request* request) {
    char* name = get_name_parameter(request);
    return render_template(env->template, name);
}

void home(Environment* env, Request* request) {
    char* response = render_response_from_env(env, request);
    printf("Response: %s\n", response);
}

int main() {
    Environment env;
    env.template = "Hello, %s!";

    Request request;
    request.name = "Alice";

    home(&env, &request);

    return 0;
}