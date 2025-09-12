#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    // other parameters can be added here
} Request;

typedef struct {
    const char *template_str;
    // other data can be added here
} Environment;

char* render_response_from_env(Environment *env, Request *req) {
    char *name = req->name;
    if (name == NULL || env->template_str == NULL) {
        return NULL;
    }
    size_t len = strlen(env->template_str) + strlen(name) + 1;
    char *response = malloc(len);
    snprintf(response, len, env->template_str, name);
    return response;
}

int main() {
    Environment env = {"Hello, %s!"};
    Request req = { "World" };
    char *response = render_response_from_env(&env, &req);
    if (response != NULL) {
        printf("%s\n", response);
        free(response);
    }
    return 0;
}