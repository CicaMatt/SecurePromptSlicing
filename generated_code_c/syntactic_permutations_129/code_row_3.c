#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "template.h"
#include "env.h"
#include "request.h"
#include "response.h"

char* render_response_from_env(Env* env) {
    Request* req = request();
    char* name = get_param("name", req);
    Template* tpl = get_template("home.html", env);
    char* rendered = render(tpl, "name", name);
    Response* resp = response(200, rendered);
    return resp;
}

Response* home(Env* env) {
    return render_response_from_env(env);
}