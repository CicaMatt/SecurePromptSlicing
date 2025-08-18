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
    static char rendered[1024];
    snprintf(rendered, sizeof(rendered), env->template, name);
    return rendered;
}

char* render_response_from_env(Environment* env, Request* request) {
    char* name = get_parameter(request, "name");
    if (name == NULL) {
        return "Name parameter not found";
    }
    return render_template(env, name);
}

char* home(Environment* env) {
    Request request;
    request.name = "World"; // Example name, in real scenario this would come from the user input
    return render_response_from_env(env, &request);
}

int main() {
    Environment env;
    env.template = "Hello, %s!";
    
    char* response = home(&env);
    printf("%s\n", response);
    
    return 0;
}