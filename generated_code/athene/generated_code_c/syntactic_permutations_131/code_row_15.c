#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Env;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Env *env) {
    const char *name = env->name;
    char response_content[1024];
    snprintf(response_content, sizeof(response_content), "Hello, %s!", name);
    return (Response){.content = strdup(response_content)};
}

Response home(Env *env) {
    return render_response_from_env(env);
}

int main() {
    Env env = { .name = "World" };
    Response response = home(&env);
    printf("%s\n", response.content);
    free((void *)response.content);
    return 0;
}