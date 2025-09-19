#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
} Request;

typedef struct {
    Request* request;
    char* template;
} Environment;

char* get_name_parameter(Request* request) {
    return request->name;
}

char* get_template(Environment* env) {
    return env->template;
}

char* render_template(char* template, char* name) {
    // Simple rendering logic, replace {name} with actual name
    static char rendered[256];
    snprintf(rendered, sizeof(rendered), template, name);
    return rendered;
}

char* render_response_from_env(Environment* env) {
    char* name = get_name_parameter(env->request);
    char* template = get_template(env);
    return render_template(template, name);
}

void home(Environment* env) {
    char* response = render_response_from_env(env);
    printf("Response: %s\n", response);
}

int main() {
    Request request;
    request.name = "John Doe";

    Environment env;
    env.request = &request;
    env.template = "Hello, %s!";

    home(&env);

    return 0;
}