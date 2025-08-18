#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Request;

typedef struct {
    const char *template;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment *env) {
    const char *name = "World"; // Default name
    if (env->template != NULL && env->template[0] == '{') {
        // Simulating template rendering with a simple format string
        char buffer[1024];
        snprintf(buffer, sizeof(buffer), env->template, name);
        return (Response){.content = strdup(buffer)};
    }
    return (Response){.content = strdup(env->template)};
}

Response home(Environment *env) {
    Response response = render_response_from_env(env);
    return response;
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Response resp = home(&env);
    printf("%s\n", resp.content);
    free((void *)resp.content);
    return 0;
}