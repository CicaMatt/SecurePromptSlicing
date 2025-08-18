#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 256
#define MAX_TEMPLATE_LENGTH 1024

typedef struct {
    char name[MAX_NAME_LENGTH];
} Request;

typedef struct {
    char template[MAX_TEMPLATE_LENGTH];
} Environment;

char* render_response_from_env(Environment env, const char* param_name) {
    static char response[MAX_TEMPLATE_LENGTH + MAX_NAME_LENGTH];
    snprintf(response, sizeof(response), "%s", env.template);
    char placeholder[20] = "{name}";
    if (strstr(env.template, placeholder)) {
        snprintf(response + strlen(response) - strlen(placeholder), 
                 sizeof(response) - strlen(response) + 1,
                 "%s", param_name);
    }
    return response;
}

char* home(Environment env) {
    Request request;
    strcpy(request.name, "Alice");
    
    return render_response_from_env(env, request.name);
}

int main() {
    Environment env;
    strcpy(env.template, "Hello, {name}!");

    char* response = home(env);
    printf("%s\n", response);

    return 0;
}