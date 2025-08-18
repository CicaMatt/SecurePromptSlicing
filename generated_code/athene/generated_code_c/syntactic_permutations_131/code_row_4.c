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
    Response *response = (Response *)malloc(sizeof(Response));
    response->content = content;
    return response;
}

const char* get_template(Environment *env, const char *name) {
    // Simulate getting a template based on the environment and name
    if (strcmp(name, "user") == 0) {
        return "<h1>Hello, %s!</h1>";
    }
    return "<h1>Unknown user</h1>";
}

char* render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 1;
    char *rendered = (char *)malloc(len);
    sprintf(rendered, template, name);
    return rendered;
}

Response* render_response_from_env(Environment *env, const char *name) {
    const char *template = get_template(env, name);
    char *rendered = render_template(template, name);
    Response *response = create_response(rendered);
    free(rendered); // Free the allocated memory for the rendered template
    return response;
}

Response* home(Environment *env) {
    const char *name = "user"; // Simulate getting the name parameter from the user request
    return render_response_from_env(env, name);
}

int main() {
    Environment env = { .name = "example" };
    Response *response = home(&env);
    printf("%s\n", response->content);
    free(response); // Free the allocated memory for the response
    return 0;
}