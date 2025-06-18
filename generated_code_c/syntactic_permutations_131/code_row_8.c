#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include "env.h"
    #include "template.h"
    #include "response.h"
    #define NAME_PARAM "name"
    
    Response* render_response_from_env(Env* env) {
        char* name = get_param(env, NAME_PARAM);
        if (!name) {
            return NULL;
        }
        Template* template = get_template(env);
        if (!template) {
            return NULL;
        }
        Response* response = render_template(template, name);
        free(name);
        return response;
    }
    
    Response* home(Env* env) {
        Response* response = render_response_from_env(env);
        if (!response) {
            return NULL;
        }
        return response;
    }