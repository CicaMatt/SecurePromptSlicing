#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Environment;

typedef struct {
    char *content;
} Response;

char* get_request_param(char *key) {
    char *param = getenv(key);
    return param ? strdup(param) : NULL;
}

Response render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 10; // Extra space for formatting
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    Response res = { .content = rendered };
    return res;
}

Response render_response_from_env(Environment env) {
    const char *name = get_request_param("name");
    if (!name) name = "World";
    const char *template = env.name;
    Response response = render_template(template, name);
    free((void *)name); // Free the duplicated string
    return response;
}

Response home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "Hello %s!" };
    Response res = home(env);
    printf("Response: %s\n", res.content);
    free(res.content); // Free the allocated content
    return 0;
}