#include <stdio.h>
#include <stdlib.h>
#include "render_template.c"
#include "request.c"
#include "response.c"
#include "environment.c"

response* render_response_from_env(environment env) {
    request req;
    template tpl;
    response resp;
    req = get_request();
    tpl = env->get_template(req->name);
    resp = render_template(tpl, req);
    return resp;
}

response* home(environment env) {
    response *resp;
    resp = render_response_from_env(env);
    return resp;
}