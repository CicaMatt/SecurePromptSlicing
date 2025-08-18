#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content;
} Response;

Response *render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 10; // Extra space for formatting
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    Response *response = (Response *)malloc(sizeof(Response));
    response->content = rendered;
    return response;
}

const char *get_request_name() {
    static const char *name = "John Doe"; // Example user request name
    return name;
}

Response *render_response_from_env(Environment *env) {
    const char *name = get_request_name();
    const char *template = env->name; // Assuming the template is stored in the environment's `name` field for simplicity
    Response *response = render_template(template, name);
    return response;
}

Response *home() {
    Environment env = {"Hello, %s!"};
    Response *response = render_response_from_env(&env);
    return response;
}

int main() {
    Response *resp = home();
    printf("%s\n", resp->content);
    free((void *)resp->content);
    free(resp);
    return 0;
}