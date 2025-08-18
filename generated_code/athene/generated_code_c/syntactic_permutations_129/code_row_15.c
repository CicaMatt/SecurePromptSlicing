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
    if (env == NULL || env->name == NULL) {
        return (Response){.content = "Hello, World!"};
    }
    size_t len = strlen("Hello, ") + strlen(env->name) + 1;
    char *greeting = malloc(len);
    snprintf(greeting, len, "Hello, %s!", env->name);
    Response response = { .content = greeting };
    return response;
}

Response home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {.name = "User"};
    Response response = home(&env);
    printf("%s\n", response.content);
    free((char *)response.content);
    return 0;
}