#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
    const char* template;
} Environment;

typedef struct {
    const char* content;
} Response;

Response render_response_from_env(Environment env) {
    const char* name = env.name;
    const char* template = env.template;
    size_t len = strlen(template) + strlen(name) + 1;
    char* rendered = malloc(len);
    snprintf(rendered, len, template, name);
    Response response = { .content = rendered };
    return response;
}

Response home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "World", .template = "Hello, %s!" };
    Response res = home(env);
    printf("%s\n", res.content);
    free((void*)res.content);
    return 0;
}