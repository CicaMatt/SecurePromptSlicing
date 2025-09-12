#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
    const char *template;
} Environment;

typedef struct {
    const char *content;
} Response;

Response* create_response(const char *content) {
    Response *response = malloc(sizeof(Response));
    response->content = content;
    return response;
}

const char* get_request_parameter(const char *env_name, const char *param) {
    if (strcmp(env_name, "name") == 0) {
        return param;
    }
    return NULL;
}

const char* get_template_from_env(Environment *env) {
    return env->template;
}

Response* render_response_from_env(Environment *env) {
    const char *name = get_request_parameter("name", env->name);
    const char *template = get_template_from_env(env);
    char rendered[256];
    snprintf(rendered, sizeof(rendered), template, name);
    return create_response(rendered);
}

Response* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"World", "Hello, %s!"};
    Response *response = home(&env);
    printf("%s\n", response->content);
    free(response);
    return 0;
}