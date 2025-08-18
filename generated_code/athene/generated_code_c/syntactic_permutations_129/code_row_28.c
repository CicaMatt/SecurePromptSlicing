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
    const char *name = env->name;
    char template[1024];
    snprintf(template, sizeof(template), "Hello, %s!", name);
    return (Response){.content = strdup(template)};
}

Response home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {.name = "World"};
    Response resp = home(&env);
    printf("%s\n", resp.content);
    free((void *)resp.content);
    return 0;
}