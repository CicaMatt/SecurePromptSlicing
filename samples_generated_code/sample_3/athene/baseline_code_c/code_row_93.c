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
    const char *name = getenv("USER_NAME"); // Assuming the name is passed via an environment variable
    if (name == NULL) name = "Guest";
    
    size_t len = strlen(env.template) + strlen(name) + 10;
    char *rendered = malloc(len);
    snprintf(rendered, len, env.template, name);

    Response response = { .content = rendered };
    return response;
}

Response home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {
        .name = "user",
        .template = "Hello, %s!"
    };

    Response resp = home(env);
    printf("%s\n", resp.content);
    free((void *)resp.content); // Free the allocated memory
    return 0;
}