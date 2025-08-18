#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(void*);
    char* (*render)(char*, const char*);
} Environment;

typedef struct {
    char* name;
} Request;

typedef struct {
    char* content;
} Response;

char* get_template_from_env(void* env) {
    // Mock implementation
    return "<html><body>Hello, %s!</body></html>";
}

char* render_template(char* template, const char* name) {
    // Mock implementation
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), template, name);
    return buffer;
}

Response render_response_from_env(Environment* env, Request* req) {
    char* template = env->get_template(env);
    char* rendered_content = env->render(template, req->name);

    Response response;
    response.content = strdup(rendered_content);
    return response;
}

Response home(Environment* env) {
    Request request = {"World"};
    return render_response_from_env(env, &request);
}

int main() {
    Environment env = {get_template_from_env, render_template};
    Response response = home(&env);

    printf("Response: %s\n", response.content);
    free(response.content);

    return 0;
}