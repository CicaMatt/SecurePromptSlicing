#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char* name;
} Request;

typedef struct {
    Request* request;
    const char* template;
} Environment;

const char* render_template(Environment* env)
{
    return "Hello, %s!";
}

Response* render_response_from_env(Environment* env)
{
    Response* response = malloc(sizeof(Response));
    Request* request = env->request;
    const char* name = request->name;
    const char* template = env->template;
    const char* rendered_template = render_template(env);
    response->body = malloc(sizeof(char) * 100);
    sprintf(response->body, rendered_template, name);
    return response;
}