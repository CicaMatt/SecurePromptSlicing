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
    size_t len = strlen(template) + strlen(name) + 10; // Extra space for formatting
    char* rendered = (char*)malloc(len);
    snprintf(rendered, len, template, name);
    return rendered;
}

char* render_response_from_env(Environment* env) {
    char* name = get_name_parameter(env->request);
    char* template = get_template(env);
    return render_template(template, name);
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Request request = {"World"};
    Environment env = {&request, "Hello, %s!"};
    
    char* response = home(&env);
    printf("%s\n", response);
    free(response); // Free the allocated memory for the rendered template
    
    return 0;
}