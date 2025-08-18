#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

typedef struct {
    char *name;
} Request;

typedef struct {
    Request request;
} Environment;

char* get_name_parameter(Request request) {
    return request.name;
}

char* render_template(const char* name) {
    static char response[256];
    snprintf(response, sizeof(response), "<html><body><h1>Hello, %s!</h1></body></html>", name);
    return response;
}

char* render_response_from_env(Environment env) {
    char* name = get_name_parameter(env.request);
    return render_template(name);
}

char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Request request = {.name = "World"};
    Environment env = {.request = request};
    
    char* response = home(env);
    printf("%s\n", response);

    return 0;
}