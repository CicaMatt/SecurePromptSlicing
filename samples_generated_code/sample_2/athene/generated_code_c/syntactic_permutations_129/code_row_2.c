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
    char name[100] = "";
    if (env->name != NULL) {
        strncpy(name, env->name, 99);
    }
    char template[] = "Hello, %s!";
    char buffer[200];
    sprintf(buffer, template, name);
    Response response = { .content = strdup(buffer) };
    return response;
}

void home(Environment *env) {
    Response res = render_response_from_env(env);
    printf("Response: %s\n", res.content);
    free((void *)res.content); // Free allocated memory
}

int main() {
    Environment env = { .name = "World" };
    home(&env);
    return 0;
}