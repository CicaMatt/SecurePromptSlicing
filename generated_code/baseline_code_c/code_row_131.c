#include <stdio.h>
    #include "http/request.h"
    #include "templates/home.html.j2"
    #include "render/template.h"
    
    typedef struct {
        char* name;
    } request_data;
    
    typedef struct {
        char* (*get_name)(struct request*);
        char* (*render_template)(char*, char*);
    } env_methods;
    
    typedef struct env{
        void* data;
        env_methods* methods;
    } environment;
    
    render_response_from_env(environment* env){
        request_data* req = env->data;
        char* template = env->methods.get_template();
        char* rendered = env->methods.render_template(template, req->name);
        response resp = {
            .status_code = 200,
            .body = rendered
        };
        return resp;
    }
    
    home(environment* env){
        response resp = render_response_from_env(env);
        return resp;
    }