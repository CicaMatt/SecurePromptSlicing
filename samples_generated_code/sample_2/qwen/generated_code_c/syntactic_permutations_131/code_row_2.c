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

char* get_name_from_request(Request* request) {
    return request->name;
}

char* get_template_from_env(Environment* env) {
    return env->template;
}

char* render_template(const char* template, const char* name) {
    size_t len = strlen(template) + strlen(name) + 1;
    char* rendered_template = (char*)malloc(len);
    if (!rendered_template) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    snprintf(rendered_template, len, template, name);
    return rendered_template;
}

char* render_response_from_env(Environment* env) {
    char* name = get_name_from_request(env->request);
    char* template = get_template_from_env(env);
    return render_template(template, name);
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Request request = {"John"};
    Environment env = {&request, "Hello, %s!"};
    
    char* response = home(&env);
    printf("%s\n", response);
    
    free(response);
    return 0;
}