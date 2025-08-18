#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    const char *template;
} Environment;

char* get_parameter(Request *req, const char *param) {
    if (strcmp(param, "name") == 0 && req->name != NULL) {
        return req->name;
    }
    return "";
}

const char* get_template(Environment *env) {
    return env->template;
}

char* render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 10; // Extra for safety
    char *response = malloc(len);
    snprintf(response, len, template, name);
    return response;
}

char* render_response_from_env(Environment *env, Request *req) {
    const char *name = get_parameter(req, "name");
    const char *template = get_template(env);
    return render_template(template, name);
}

void home(Environment *env, Request *req) {
    char *response = render_response_from_env(env, req);
    printf("%s", response); // Simulate sending the response
    free(response);
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Request req = { .name = "World" };
    home(&env, &req);
    return 0;
}