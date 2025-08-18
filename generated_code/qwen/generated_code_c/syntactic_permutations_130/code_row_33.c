#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_parameter)(void*, const char*);
    char* (*get_template)(void*);
} Environment;

char* render_template(const char* template, const char* name) {
    char* response = malloc(strlen(template) + strlen(name) + 1);
    sprintf(response, template, name);
    return response;
}

char* render_response_from_env(Environment* env) {
    const char* name = env->get_parameter(env, "name");
    const char* template = env->get_template(env);
    return render_template(template, name);
}

typedef struct {
    Environment env;
} Request;

char* get_parameter(Request* req, const char* param_name) {
    if (strcmp(param_name, "name") == 0) {
        return "World"; // Example default value
    }
    return NULL;
}

char* get_template(Request* req) {
    return "Hello, %s!";
}

int main() {
    Request request = {{(void* (*)(void*, const char*))get_parameter, (void* (*)(void*))get_template}};
    Environment* env = (Environment*)&request;

    char* response = render_response_from_env(env);
    printf("%s\n", response);
    free(response);

    return 0;
}