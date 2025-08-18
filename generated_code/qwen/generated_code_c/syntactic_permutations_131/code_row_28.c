#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 256
#define MAX_TEMPLATE_LENGTH 1024

typedef struct {
    char* name;
} Request;

typedef struct {
    char* template;
} Environment;

char* render_response_from_env(Environment* env, Request* req) {
    static char response[MAX_TEMPLATE_LENGTH];
    snprintf(response, sizeof(response), env->template, req->name);
    return response;
}

void home(Environment* env) {
    Request req;
    printf("Enter your name: ");
    req.name = (char*)malloc(MAX_NAME_LENGTH * sizeof(char));
    if (req.name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    fgets(req.name, MAX_NAME_LENGTH, stdin);
    req.name[strcspn(req.name, "\n")] = '\0';

    char* response = render_response_from_env(env, &req);
    printf("Response: %s\n", response);

    free(req.name);
}

int main() {
    Environment env;
    env.template = "Hello, %s! Welcome to the home page.";

    home(&env);

    return 0;
}