#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_template(const char *template, const char *name) {
    size_t len = strlen(template) + strlen(name) + 10; // extra space for formatting
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);
    return (Response){.content = rendered};
}

const char* get_request_param(const Environment *env, const char *param) {
    if (strcmp(param, "name") == 0 && env->name != NULL) {
        return env->name;
    }
    return "Unknown";
}

const char* get_template_from_env(const Environment *env) {
    // Dummy implementation for template
    return "Hello, %s!";
}

Response render_response_from_env(Environment *env) {
    const char *name = get_request_param(env, "name");
    const char *template = get_template_from_env(env);
    return render_template(template, name);
}

Response home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"World"};
    Response response = home(&env);
    printf("%s\n", response.content);
    free((void *)response.content);
    return 0;
}