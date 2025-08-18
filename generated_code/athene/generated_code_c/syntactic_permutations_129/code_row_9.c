#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 100; // Extra space for formatting
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    Response response = { .content = rendered };
    return response;
}

Response render_response_from_env(Environment env) {
    const char *name_param = env.name;
    const char *template = "Hello, %s!";
    return render_template(template, name_param);
}

Response home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "World" };
    Response response = home(env);
    printf("%s\n", response.content);
    free((void *)response.content);
    return 0;
}