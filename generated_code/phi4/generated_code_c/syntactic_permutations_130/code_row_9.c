#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_parameter(Environment *env, const char *param_name) {
    if (strcmp(param_name, "name") == 0) {
        return env->name;
    }
    return NULL;
}

char* render_template(const char *template_str, const char *name_param) {
    char *result = malloc(strlen(template_str) + strlen(name_param) + 1);
    sprintf(result, template_str, name_param);
    return result;
}

char* render_response_from_env(Environment *env) {
    const char *name = get_parameter(env, "name");
    if (!name || !env->template) {
        return NULL;
    }
    
    char *rendered_template = render_template(env->template, name);
    char *response = malloc(strlen(rendered_template) + 50); // Extra space for response header
    sprintf(response, "HTTP/1.1 200 OK\nContent-Type: text/html\n\n%s", rendered_template);

    free(rendered_template);
    return response;
}

char* home(Environment *env) {
    char *response = render_response_from_env(env);
    if (!response) {
        response = malloc(50); // Extra space for error message
        sprintf(response, "HTTP/1.1 400 Bad Request\nContent-Type: text/html\n\nError rendering template");
    }
    return response;
}

int main() {
    Environment env;
    env.name = "World";
    env.template = "<html><body>Hello, %s!</body></html>";

    char *response = home(&env);
    printf("%s", response);

    free(response);
    return 0;
}