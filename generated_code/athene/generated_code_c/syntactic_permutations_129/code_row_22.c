#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
} Environment;

typedef struct {
    const char* content;
} Response;

Response render_response_from_env(Environment *env) {
    const char* name = env->name;
    const char* template = "<html><body>Hello, %s!</body></html>";
    size_t len = strlen(template) + strlen(name);
    char *rendered = malloc(len + 1);
    snprintf(rendered, len + 1, template, name);
    Response response = { .content = rendered };
    return response;
}

Response home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "World" };
    Response response = home(&env);
    printf("%s\n", response.content);
    free((void *)response.content);
    return 0;
}