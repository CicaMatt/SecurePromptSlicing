#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

typedef struct {
    char *content;
} Response;

Response* create_response(const char *content) {
    Response *response = (Response*)malloc(sizeof(Response));
    response->content = strdup(content);
    return response;
}

void free_response(Response *response) {
    free(response->content);
    free(response);
}

char* render_template(const char *template, const char *name) {
    char *rendered = (char*)malloc(strlen(template) + strlen(name) + 1);
    sprintf(rendered, template, name);
    return rendered;
}

Response* render_response_from_env(Environment *env) {
    char *rendered_template = render_template(env->template, env->name);
    Response *response = create_response(rendered_template);
    free(rendered_template);
    return response;
}

Response* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"John Doe", "Hello, %s!"};
    Response *response = home(&env);

    printf("Response: %s\n", response->content);

    free_response(response);
    return 0;
}