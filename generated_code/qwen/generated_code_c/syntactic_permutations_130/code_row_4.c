#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    Request *request;
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
    char *rendered = (char *)malloc(strlen(template) + strlen(name) + 1);
    sprintf(rendered, template, name);
    return rendered;
}

Response* render_response_from_env(Environment *env) {
    const char *name = env->request->name;
    const char *template = env->template;
    char *rendered_content = render_template(template, name);
    Response *response = create_response(rendered_content);
    free(rendered_content);
    return response;
}

Response* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Request request = {"John Doe"};
    Environment env = {&request, "Hello, %s!"};
    
    Response *response = home(&env);
    printf("%s\n", response->content);
    
    destroy_response(response);
    return 0;
}