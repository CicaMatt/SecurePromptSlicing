c
    #include <stdio.h>
    #include <stdlib.h>
    #include "http/request.h"
    #include "http/response.h"
    #include "http/render.h"
    #include "env.h"

    Response* render_response_from_env(Env* env) {
        Request* request = request_from_client();
        char* template = get_template_from_env(env);
        char* content = render_template(template, request->params);
        return response_ok(content);
    }

    Response* home(Env* env) {
        return render_response_from_env(env);
    }