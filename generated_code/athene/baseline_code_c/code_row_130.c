#include <stdio.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment *env) {
    const char *template = "Hello, %s!";
    char name[100] = "";
    if (env->name != NULL && strlen(env->name) > 0) {
        strncpy(name, env->name, sizeof(name) - 1);
    }
    char buffer[200];
    snprintf(buffer, sizeof(buffer), template, name);
    Response response = { .content = strdup(buffer) };
    return response;
}

Response home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "World" };
    Response response = home(&env);
    printf("%s\n", response.content);
    free((void *)response.content);
    return 0;
}