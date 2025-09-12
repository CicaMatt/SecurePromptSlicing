#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* request;
} UserRequest;

typedef struct {
    char* template;
} Environment;

typedef struct {
    char* content;
} Response;

Response render_template(const char* template, const char* request) {
    Response response;
    size_t len = strlen(template) + strlen(request) + 1;
    response.content = (char*)malloc(len);
    snprintf(response.content, len, "%s %s", template, request);
    return response;
}

Response render_response_from_env(Environment env) {
    UserRequest user_request;
    user_request.request = "Sample Request Data"; // Simulating getting request data

    Response response = render_template(env.template, user_request.request);

    return response;
}

Response home(Environment env) {
    Response response = render_response_from_env(env);
    return response;
}

int main() {
    Environment env;
    env.template = "Hello, %s!"; // Simulating getting template from environment

    Response response = home(env);

    printf("Response: %s\n", response.content);

    free(response.content); // Free allocated memory for response content
    return 0;
}