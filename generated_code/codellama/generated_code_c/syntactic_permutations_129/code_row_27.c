#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(struct Environment*);
} Environment;

char* render_response_from_env(Environment* env) {
    char* template = env->get_template(env);
    char* response = malloc(100 + strlen(template));
    sprintf(response, "Hello, %s!", name);
    return response;
}

int main() {
    Environment env;
    env.get_template = &get_template; // this is just an example
    char* response = render_response_from_env(&env);
    printf("%s\n", response);
    free(response); // don't forget to free memory!
}