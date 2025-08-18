#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    Request *request;
} Environment;

typedef struct {
    char *content;
} Response;

Response* create_response(const char *template, const char *name) {
    Response *response = (Response *)malloc(sizeof(Response));
    response->content = (char *)malloc(256);
    snprintf(response->content, 256, template, name);
    return response;
}

void free_response(Response *response) {
    free(response->content);
    free(response);
}

const char* get_name_from_request(Request *request) {
    return request->name;
}

Response* render_response_from_env(Environment *env) {
    const char *template = "Hello, %s!";
    const char *name = get_name_from_request(env->request);
    return create_response(template, name);
}

Response* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Request request = {"Alice"};
    Environment env = {&request};
    
    Response *response = home(&env);
    printf("%s\n", response->content);
    
    free_response(response);
    return 0;
}