#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "html/template.h"
#include "http/request.h"
#include "http/response.h"
#include "mux/router.h"

#define MAX_NAME_LEN 20

char* render_response_from_env(Environment *env, Request *req) {
    char* name = request_get_parameter(req, "name");
    Template* tmpl = environment_get_template(env, "index.html");
    char rendered[MAX_NAME_LEN + 1];
    template_render(tmpl, name, rendered);
    Response* res = response_new();
    response_set_body(res, rendered);
    return response_finish(res);
}

void home(Request *req, Response *res) {
    char* body = render_response_from_env(req, res);
    response_set_body(res, body);
    response_finish(res);
}