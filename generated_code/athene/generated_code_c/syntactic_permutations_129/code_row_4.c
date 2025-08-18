#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content;
} Response;

Response* create_response(const char *content) {
    Response *response = malloc(sizeof(Response));
    response->content = content;
    return response;
}

const char* get_request_name(Environment *env) {
    return env->name ? env->name : "World";
}

char* render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 10; // Extra space for formatting
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

Response* render_response_from_env(Environment *env) {
    const char *name = get_request_name(env);
    const char *template = "Hello, %s!";
    char *rendered_template = render_template(template, name);
    Response *response = create_response(rendered_template);
    free(rendered_template);
    return response;
}

Response* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "User" };
    Response *response = home(&env);
    printf("%s\n", response->content);
    free(response);
    return 0;
}