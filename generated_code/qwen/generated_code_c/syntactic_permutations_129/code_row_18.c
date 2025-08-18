#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_TEMPLATE_LENGTH 500

typedef struct {
    char* name;
} Request;

typedef struct {
    char* template;
} Environment;

void render_response_from_env(Environment env, Request req) {
    char output[MAX_TEMPLATE_LENGTH];
    snprintf(output, sizeof(output), env.template, req.name);
    printf("%s", output);
}

int main() {
    Environment env = {"Hello, %s!"};
    Request req = {"Alice"};
    
    render_response_from_env(env, req);
    
    return 0;
}