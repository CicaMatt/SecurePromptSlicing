#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    struct Environment {
        char template[1024];
    };
    
    struct Request {
        char name[56];
    };
    
    struct Response {
        char body[1024];
    };
    
    void render_response_from_env(struct Environment* env, struct Request* req) {
        struct Response res;
        strcpy(res.body, env->template);
        return res;
    }
    
    void home(struct Environment* env, struct Request* req) {
        render_response_from_env(env, req);
    }