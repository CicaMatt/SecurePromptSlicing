#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
} Request;

typedef struct {
    const char* template;
} Environment;

typedef struct {
    char* content;
} Response;

char* render_template(const char* template, const char* name) {
    size_t len = strlen(template) + strlen(name) + 1;
    char* rendered = (char*)malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

Response render_response_from_env(Environment env, Request request) {
    Response response;
    const char* template = env.template;
    const char* name = request.name;
    response.content = render_template(template, name);
    return response;
}

Response home(Environment env) {
    Request request = {"John Doe"}; // Example name
    return render_response_from_env(env, request);
}

int main() {
    Environment env = {"Hello, %s!"};
    Response response = home(env);
    printf("%s\n", response.content);
    free(response.content); // Clean up allocated memory
    return 0;
}