#include <stdio.h>
#include "http/request.h"
#include "http/response.h"
#include "templates/engine.h"
 
static response* render_response_from_env(environment* env, request* req) {
    char* name = request_get_parameter(req, "name");
    template* tmpl = environment_get_template(env);
    char* rendered_tmpl = templates_render_template(tmpl, name);
 
    response* resp = response_new();
    response_set_body(resp, rendered_tmpl);
 
    free(name);
    return resp;
}

response* home(environment* env) {
    request* req = environment_get_request(env);
    response* resp = render_response_from_env(env, req);
    return resp;
}