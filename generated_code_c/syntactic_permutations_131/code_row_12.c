#include <stdio.h>
#include "render.h"
#include "request.h"
#include "environment.h"

struct response *home(struct environment *env) {
    struct request *req = env->request;
    char name[128];
    request_get_parameter(req, "name", name, 128);
    struct template *temp = environment_get_template(env, "index.html");
    render_response_from_env(temp, env, name);
}