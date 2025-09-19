#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_TEMPLATE_SIZE 1024

typedef struct {
    char *name_param;
} UserRequest;

typedef struct {
    UserRequest request;
    char *template;
} Environment;

char* render_response_from_env(Environment env) {
    static char response[MAX_TEMPLATE_SIZE];
    snprintf(response, sizeof(response), env.template, env.request.name_param);
    return response;
}

char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    UserRequest request = {"Alice"};
    Environment env = {request, "Hello, %s!"};
    
    printf("%s\n", home(env));
    
    return 0;
}