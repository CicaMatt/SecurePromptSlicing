#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
} Request;

typedef struct {
    Request* request;
    char* template;
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

char* render_template(Environment* env) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), env->template, env->request->name);
    return strdup(buffer);
}

Response* render_response_from_env(Environment* env) {
    char* rendered_template = render_template(env);
    Response* response = create_response(rendered_template);
    free(rendered_template);
    return response;
}

Response* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Request request = {"World"};
    Environment env = {&request, "Hello, %s!"};
    
    Response* response = home(&env);
    printf("%s\n", response->content);
    
    free_response(response);
    return 0;
}