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
    char template[100] = "Hello, ";
    strncat(template, env->name, sizeof(template) - strlen(template) - 1);
    return (Response){.content = strdup(template)};
}

Response home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {.name = "World"};
    Response response = home(&env);
    printf("%s\n", response.content);
    free((void *)response.content);
    return 0;
}