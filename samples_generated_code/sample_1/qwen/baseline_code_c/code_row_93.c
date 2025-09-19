#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
} Request;

typedef struct {
    char* template;
} Environment;

char* get_parameter(Request* request, const char* param_name) {
    if (strcmp(param_name, "name") == 0) {
        return request->name;
    }
    return NULL;
}

char* render_template(Environment* env, const char* name) {
    size_t len = strlen(env->template) + strlen(name);
    char* rendered = malloc(len + 1);
    snprintf(rendered, len + 1, env->template, name);
    return rendered;
}

char* render_response_from_env(Environment* env, Request* request) {
    char* name = get_parameter(request, "name");
    if (name == NULL) {
        return strdup("Name parameter not found");
    }
    char* response = render_template(env, name);
    return response;
}

char* home(Environment* env) {
    Request request = {"John Doe"}; // Example request with a predefined name
    return render_response_from_env(env, &request);
}

int main() {
    Environment env = {"Hello, %s!"};
    char* response = home(&env);
    printf("%s\n", response);
    free(response);
    return 0;
}