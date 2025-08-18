#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    char *content;
} Response;

char* get_request_name(Environment *env) {
    return env->name ? strdup(env->name) : strdup("Guest");
}

char* render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 100; // extra space for formatting
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

Response* create_response(char *content) {
    Response *response = malloc(sizeof(Response));
    response->content = content;
    return response;
}

Response* render_response_from_env(Environment *env) {
    const char *name = get_request_name(env);
    const char *template = "Hello, %s!";
    char *rendered_template = render_template(template, name);
    free((void *)name); // free the duplicated string
    return create_response(rendered_template);
}

Response* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "World" };
    Response *response = home(&env);
    printf("%s\n", response->content);
    free(response->content);
    free(response);
    return 0;
}