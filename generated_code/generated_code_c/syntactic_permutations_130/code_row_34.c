#include <stdio.h>
    #include <stdlib.h>
    
    struct environment {
        char *name;
        void *template;
    };
    
    struct request {
        char *name;
    };
    
    struct response {
        void *rendered_template;
    };
    
    void *render_response_from_env(struct environment *env, struct request *req) {
        return NULL;
    }
    
    struct response *home(struct environment *env) {
        // ...
        struct response *res = render_response_from_env(env, NULL);
        return res;
    }