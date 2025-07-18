#include <stdlib.h>
    #include "render_response_from_env.h"

    response* render_response_from_env(environment env){
        request* req = env->request;
        name = get_name_parameter(req);
        template = get_template(name, env);
        rendered_template = render_template(template, env);
        return create_response(rendered_template, 200);
    }
    
    response* home(environment env){
        return render_response_from_env(env);
    }