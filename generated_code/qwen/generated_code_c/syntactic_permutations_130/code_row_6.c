#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define TEMPLATE "Hello, %s!\n"

typedef struct {
    char *name;
} Request;

typedef struct {
    Request request;
} Environment;

char* render_response_from_env(Environment env) {
    static char response[256];
    snprintf(response, sizeof(response), TEMPLATE, env.request.name);
    return response;
}

char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    env.request.name = "World";

    printf("%s", home(env));

    return 0;
}