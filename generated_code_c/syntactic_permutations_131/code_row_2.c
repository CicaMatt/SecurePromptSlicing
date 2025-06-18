#include <stdio.h>
#include <stdlib.h>
#include "http/request.h"
#include "http/response.h"
#include "templates/template.h"
#include "render/render.h"

Response* render_response_from_env(Environment* env){
    Request* req = request_new();
    char* name = req->get_parameter("name");
    Template* tmpl = env->get_template("home.html");
    char* body = render_template(tmpl, name);
    Response* res = response_new();
    res->set_body(body);
    return res;
}
Response* home(Environment* env){
    return render_response_from_env(env);
}