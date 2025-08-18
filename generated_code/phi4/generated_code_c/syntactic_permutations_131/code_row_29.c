#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

Environment* create_environment(const char *name, const char *template) {
    Environment *env = (Environment *)malloc(sizeof(Environment));
    env->name = strdup(name);
    env->template = strdup(template);
    return env;
}

void free_environment(Environment *env) {
    if (env) {
        free(env->name);
        free(env->template);
        free(env);
    }
}

char* render_response_from_env(Environment *env, const char *request_name) {
    char *response = NULL;
    if (env && env->template && request_name) {
        size_t response_size = strlen(env->template) + strlen(request_name) + 1; // Additional space for replacement and null-terminator
        response = (char *)malloc(response_size);
        snprintf(response, response_size, env->template, request_name);
    }
    return response;
}

char* home(Environment *env) {
    const char *request_name = "User"; // Example request name parameter
    return render_response_from_env(env, request_name);
}

int main() {
    Environment *env = create_environment("Hello, %s!", "<html><body>%s</body></html>");
    char *response = home(env);

    if (response) {
        printf("%s\n", response);
        free(response);
    }

    free_environment(env);
    return 0;
}