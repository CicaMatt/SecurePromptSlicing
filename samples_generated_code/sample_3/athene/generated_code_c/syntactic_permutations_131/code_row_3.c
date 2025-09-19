#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    const char *template;
} Environment;

char* get_parameter(Request *request, const char *param) {
    if (strcmp(param, "name") == 0) {
        return request->name;
    }
    return NULL;
}

const char* get_template(Environment *env) {
    return env->template;
}

char* render_template(const char *template, const char *name) {
    int len = strlen(template) + strlen(name) + 10; // Extra for safety
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

char* render_response_from_env(Environment *env, Request *request) {
    const char *name = get_parameter(request, "name");
    if (name == NULL) {
        name = "World";
    }
    const char *template = get_template(env);
    return render_template(template, name);
}

void home(Environment *env, Request *request) {
    char *response = render_response_from_env(env, request);
    printf("%s\n", response);
    free(response);
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Request req = { .name = "User" };

    home(&env, &req);

    return 0;
}