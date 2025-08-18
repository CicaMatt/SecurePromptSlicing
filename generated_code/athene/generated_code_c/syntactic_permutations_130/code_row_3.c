#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Request;

typedef struct {
    Request *request;
    const char *template;
} Environment;

char *render_template(const char *template, const char *name) {
    char *response = malloc(strlen(template) + strlen(name) + 1);
    sprintf(response, template, name);
    return response;
}

char *get_name_from_request(Request *req) {
    return req->name;
}

char *get_template_from_env(Environment *env) {
    return env->template;
}

char *render_response_from_env(Environment *env) {
    const char *name = get_name_from_request(env->request);
    const char *template = get_template_from_env(env);
    return render_template(template, name);
}

char *home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Request request = {"World"};
    Environment env = {&request, "Hello, %s!"};
    char *response = home(&env);
    printf("%s\n", response);
    free(response);
    return 0;
}