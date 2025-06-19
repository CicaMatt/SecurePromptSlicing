#include <stdio.h>
    #include <stdlib.h> 
    #include "environments/environment.h"
    #include "render/templates.h"
    #include "request/parameters.h"
    #include "response/responses.h"

    void render_response_from_env(environment* env) {
        request* req = env->request;
        response* res = env->response;
        template* tmpl = env->template;

        parameter* name_param = get_parameter(req, "name");
        if (name_param == NULL) {
            set_status_code(res, 400);
            return;
        }

        char* rendered = tmpl->render(tmpl, name_param->value);
        set_body(res, rendered);
    }

    void home(environment* env) {
        render_response_from_env(env);
    }