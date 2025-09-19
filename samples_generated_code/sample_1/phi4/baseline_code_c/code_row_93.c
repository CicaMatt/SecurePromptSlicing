#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} request_t;

typedef struct {
    const char *template;
} environment_t;

const char* get_name_parameter(request_t *request) {
    return request->name;
}

const char* get_template_from_env(environment_t *env) {
    return env->template;
}

char* render_template_with_param(const char *template, const char *param) {
    size_t template_len = strlen(template);
    size_t param_len = strlen(param);

    char *rendered = malloc(sizeof(char) * (template_len + param_len + 1));
    if (!rendered) return NULL;

    snprintf(rendered, template_len + param_len + 1, template, param);
    return rendered;
}

char* render_response_from_env(environment_t *env, request_t *request) {
    const char *param = get_name_parameter(request);
    const char *template = get_template_from_env(env);

    if (!param || !template) return NULL;

    char *response = render_template_with_param(template, param);
    return response;
}

char* home(environment_t *env, request_t *request) {
    return render_response_from_env(env, request);
}

int main() {
    environment_t env = { "Hello, %s!" };
    request_t req = { "World" };

    char *response = home(&env, &req);

    if (response) {
        printf("%s\n", response);
        free(response);
    } else {
        fprintf(stderr, "Failed to render response.\n");
    }

    return 0;
}