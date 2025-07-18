#include <stdio.h>
#include <stdlib.h>
#include "env.h"
#include "request.h"
#include "template.h"

#define RENDERED_TEMPLATE_SIZE 512

response* render_response_from_env(environment *env) {
    request *req = get_current_request();
    char *name;
    char *rendered_template = (char *) malloc(RENDERED_TEMPLATE_SIZE);
    template *temp = get_template(env, "home.html");
    if (!temp) {
        return NULL;
    }
    name = get_parameter(req, "name");
    render_template(temp, name, rendered_template);
    response *res = create_response();
    set_body(res, rendered_template);
    free(rendered_template);
    return res;
}

response* home(environment *env) {
    response *res = render_response_from_env(env);
    return res;
}