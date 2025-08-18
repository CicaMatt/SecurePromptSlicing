#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_template)(void);
} Environment;

typedef struct {
    const char* name;
} Request;

typedef struct {
    const char* content;
} Response;

const char* get_name_from_request(const Request* request) {
    return request->name;
}

Response render_response_from_env(Environment* env, Request* request) {
    const char* template = env->get_template();
    const char* name = get_name_from_request(request);
    char* rendered_content = malloc(strlen(template) + strlen(name) + 1);
    sprintf(rendered_content, template, name);
    Response response = { .content = rendered_content };
    return response;
}

const char* home_get_template(void) {
    return "Hello, %s!";
}

Response home(Environment* env) {
    Request request = { .name = "World" };
    return render_response_from_env(env, &request);
}

int main() {
    Environment env = { .get_template = home_get_template };
    Response response = home(&env);
    printf("%s\n", response.content);
    free((void*)response.content);
    return 0;
}