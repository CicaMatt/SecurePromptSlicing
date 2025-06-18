#include <stdio.h>
#include <stdlib.h>
#include "templates/home.html"
#include "render.h"

typedef struct {
    char* name;
} request;

typedef struct {
    char* content_type;
    int status_code;
    char* body;
} response;

void render(char* template, void* data, char** rendered) {
    // implementation not shown
}

response render_response_from_env(request req, void* env) {
    char* name = get_name_from_request(req);
    char* template = get_template_from_env(env);
    char rendered[1024];
    render(template, (void*) &name, &rendered);
    response resp;
    resp.content_type = "text/html";
    resp.status_code = 200;
    resp.body = rendered;
    return resp;
}

response home(request req) {
    void* env;
    response resp = render_response_from_env(req, env);
    return resp;
}