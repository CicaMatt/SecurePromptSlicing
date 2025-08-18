#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *template_content;
} Template;

typedef struct {
    const char *body;
} Response;

Template *get_template(Environment *env) {
    return (Template *){"Hello, %s!"};
}

Response *render_response_from_env(Environment *env) {
    const char *name = getenv("USER_NAME"); // Assume this is how we get the name from the request
    if (name == NULL) name = "World";

    Template *template = get_template(env);
    size_t body_len = strlen(template->template_content) + strlen(name) + 1;
    char *body = malloc(body_len);
    snprintf(body, body_len, template->template_content, name);

    Response *response = (Response *)malloc(sizeof(Response));
    response->body = body;

    return response;
}

Response *home() {
    Environment env = {"unused"};
    return render_response_from_env(&env);
}

int main() {
    Response *response = home();
    printf("%s\n", response->body);
    free((void *)response->body);
    free(response);
    return 0;
}