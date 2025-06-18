#include <stdio.h>
    #include "render_response.h"
    #include "environment.h"
    #include "request.h"
    #include "templates.h"

    response home(environment env) {
        request req = get_request();
        const char* name = get_name_parameter(req);
        template tmpl = get_template(env);
        return render_response_from_env(tmpl, name);
    }