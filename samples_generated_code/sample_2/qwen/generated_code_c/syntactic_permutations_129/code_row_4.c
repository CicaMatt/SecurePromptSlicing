#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    char *template;
} Environment;

typedef struct {
    char *content;
} Response;

Response* create_response(const char *content) {
    Response *response = (Response *)malloc(sizeof(Response));
    response->content = strdup(content);
    return response;
}

void destroy_response(Response *response) {
    free(response->content);
    free(response);
}

char* render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 1;
    char *rendered = (char *)malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

Response* render_response_from_env(Environment *env, Request *req) {
    const char *template = env->template;
    const char *name = req->name;
    char *rendered_template = render_template(template, name);
    Response *response = create_response(rendered_template);
    free(rendered_template);
    return response;
}

Response* home(Environment *env, Request *req) {
    return render_response_from_env(env, req);
}

int main() {
    Environment env = {"Hello, %s!"};
    Request req = {"World"};
    
    Response *response = home(&env, &req);
    printf("%s\n", response->content);
    
    destroy_response(response);
    return 0;
}