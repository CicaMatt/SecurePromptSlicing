#include <stdio.h>
    #include <stdlib.h>
    #include "render_template.h"
    
    void render_response_from_env(struct environment *env) {
        struct request *req = env->request;
        const char* name = req->get_param("name");
        const char* template = env->get_template();
        char* result = render_template(template, name);
        struct response *resp = new_response();
        resp->set_body(result);
        free(result);
        return resp;
    }
    
    void home() {
        struct environment env = create_environment();
        struct request req = create_request("GET", "/");
        env.request = &req;
        render_response_from_env(&env);
    }