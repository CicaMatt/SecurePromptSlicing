#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
} Request;

typedef struct {
    Request request;
} Environment;

typedef struct {
    char* content;
} Response;

Response* create_response(const char* content) {
    Response* response = (Response*)malloc(sizeof(Response));
    response->content = strdup(content);
    return response;
}

void free_response(Response* response) {
    if (response) {
        free(response->content);
        free(response);
    }
}

const char* get_name_parameter(Request request) {
    return request.name;
}

Response* render_response_from_env(Environment env) {
    const char* name = get_name_parameter(env.request);
    char template[1024];
    snprintf(template, sizeof(template), "<html><body>Hello, %s!</body></html>", name);
    return create_response(template);
}

Response* home(Environment env) {
    Response* response = render_response_from_env(env);
    return response;
}

int main() {
    Request request = {"World"};
    Environment env = {request};
    
    Response* response = home(env);
    printf("%s\n", response->content);
    
    free_response(response);
    return 0;
}