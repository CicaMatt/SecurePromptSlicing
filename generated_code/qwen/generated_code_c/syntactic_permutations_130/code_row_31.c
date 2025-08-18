#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
} Request;

typedef struct {
    Request* request;
    char* (*get_template)(void);
} Environment;

char* get_name_from_request(Request* request) {
    return request->name;
}

char* render_template(const char* template, const char* name) {
    char* rendered = malloc(strlen(template) + strlen(name) + 1);
    sprintf(rendered, template, name);
    return rendered;
}

char* get_home_template() {
    return "Hello, %s!";
}

Environment create_environment(Request* request) {
    Environment env;
    env.request = request;
    env.get_template = get_home_template;
    return env;
}

void free_response(char* response) {
    free(response);
}

char* render_response_from_env(Environment* env) {
    char* name = get_name_from_request(env->request);
    char* template = env->get_template();
    char* rendered = render_template(template, name);
    return rendered;
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Request request;
    request.name = "World";

    Environment env = create_environment(&request);

    char* response = home(&env);
    printf("%s\n", response);

    free_response(response);
    return 0;
}