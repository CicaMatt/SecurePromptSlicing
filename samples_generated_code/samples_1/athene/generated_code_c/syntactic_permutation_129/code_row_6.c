#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment *env) {
    char template[1024];
    if (env->name == NULL) {
        snprintf(template, sizeof(template), "Hello, Guest!");
    } else {
        snprintf(template, sizeof(template), "Hello, %s!", env->name);
    }
    Response response = { .content = strdup(template) };
    return response;
}

Response home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "World" };
    Response res = home(&env);
    printf("%s\n", res.content);
    free((void *)res.content);
    return 0;
}