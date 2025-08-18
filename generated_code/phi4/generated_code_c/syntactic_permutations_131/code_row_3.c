#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} request_t;

typedef struct {
    const char *template;
    request_t *request;
} environment_t;

const char* get_name_parameter(request_t *req) {
    return req->name;
}

char* render_template(const char *template, const char *name) {
    size_t len = snprintf(NULL, 0, template, name);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    snprintf(result, len + 1, template, name);
    return result;
}

const char* render_response_from_env(environment_t env) {
    const char *name = get_name_parameter(env.request);
    return render_template(env.template, name);
}

const char* home(environment_t env) {
    return render_response_from_env(env);
}

int main() {
    request_t req = {"World"};
    environment_t env = {
        .template = "Hello, %s!",
        .request = &req
    };

    const char *response = home(env);
    printf("%s\n", response);

    free((void*)response); // Free the memory allocated by render_template

    return 0;
}