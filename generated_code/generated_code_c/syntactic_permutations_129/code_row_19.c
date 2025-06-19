#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *render_response_from_env(request_t *req, environment_t *env) {
    char *name = get_name_parameter(req);
    template_t *template = get_template(env);
    return render(template, name);
}

response_t* home(request_t *req){
    response_t *res = (response_t*)malloc(sizeof(response_t));
    res->body = render_response_from_env(req, env);
    return res;
}