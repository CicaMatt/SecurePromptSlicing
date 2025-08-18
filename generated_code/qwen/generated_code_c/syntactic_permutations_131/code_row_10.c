#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* request;
} UserRequest;

typedef struct {
    char* template;
} Environment;

char* render_template(const char* template, const char* request) {
    // Simple rendering logic for demonstration purposes
    static char response[256];
    snprintf(response, sizeof(response), "%s rendered with %s", template, request);
    return response;
}

char* render_response_from_env(Environment* env) {
    UserRequest user_request = {"sample_request"};
    char* rendered_template = render_template(env->template, user_request.request);
    return rendered_template;
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"<h1>Hello World</h1>"};
    printf("Response: %s\n", home(&env));
    return 0;
}