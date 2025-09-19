#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    char *template;
} Environment;

char* get_name_parameter(Request *request) {
    return request->name;
}

char* get_template(Environment *env) {
    return env->template;
}

char* render_template(char *template, char *name) {
    char *rendered = malloc(strlen(template) + strlen(name) + 1);
    sprintf(rendered, template, name);
    return rendered;
}

char* render_response_from_env(Environment *env, Request *request) {
    char *name = get_name_parameter(request);
    char *template = get_template(env);
    return render_template(template, name);
}

char* home(Environment *env, Request *request) {
    return render_response_from_env(env, request);
}

int main() {
    Environment env = {"Hello, %s!"};
    Request request = {"World"};
    
    char *response = home(&env, &request);
    printf("%s\n", response);
    
    free(response);
    return 0;
}