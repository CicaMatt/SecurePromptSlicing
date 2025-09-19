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
    snprintf(response, sizeof(response), "%s %s", template, request);
    return response;
}

char* render_response_from_env(Environment* env) {
    UserRequest user_request;
    user_request.request = "Sample Request";

    const char* rendered_template = render_template(env->template, user_request.request);

    return strdup(rendered_template);
}

char* home(Environment* env) {
    char* response = render_response_from_env(env);
    return response;
}

int main() {
    Environment env;
    env.template = "Hello, this is your";

    char* response = home(&env);
    printf("Response: %s\n", response);

    free(response); // Free the duplicated string
    return 0;
}