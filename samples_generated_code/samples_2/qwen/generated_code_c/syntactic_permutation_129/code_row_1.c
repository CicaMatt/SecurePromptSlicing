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

char* render_template(Environment* env, const char* template, const char* name) {
    size_t len = strlen(template) + strlen(name) + 1;
    char* rendered_template = (char*)malloc(len * sizeof(char));
    snprintf(rendered_template, len, template, name);
    return rendered_template;
}

char* render_response_from_env(Environment* env) {
    const char* name = get_name_parameter(env->request);
    const char* template = env->template;
    return render_template(env, template, name);
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Request request = {"World"};
    Environment env = {&request, "Hello, %s!"};
    
    char* response = home(&env);
    printf("%s\n", response);
    
    free(response);
    return 0;
}