#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
    const char *template;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment env) {
    char *name = getenv("name"); // Assuming environment variables are set in the process
    if (name == NULL || strlen(name) == 0) {
        name = "World";
    }
    size_t template_len = strlen(env.template);
    size_t name_len = strlen(name);
    char *rendered_template = malloc(template_len + name_len + 1);
    snprintf(rendered_template, template_len + name_len + 1, env.template, name);

    Response response = { .content = rendered_template };
    return response;
}

Response home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {
        .name = "USER_NAME",
        .template = "Hello, %s!"
    };

    Response resp = home(env);
    printf("%s\n", resp.content);
    free((void *)resp.content); // Free allocated memory
    return 0;
}