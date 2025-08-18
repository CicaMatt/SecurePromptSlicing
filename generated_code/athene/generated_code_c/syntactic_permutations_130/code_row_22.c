#include <stdio.h>
#include <string.h>

typedef struct {
    char *request;
    char *template;
} Environment;

typedef struct {
    char *content;
} Response;

Response render_response_from_env(Environment env) {
    char name[100];
    sscanf(env.request, "name=%s", name);
    
    char response_content[500];
    sprintf(response_content, env.template, name);

    Response response = { .content = strdup(response_content) };
    return response;
}

Response home(Environment env) {
    return render_response_from_env(env);
}