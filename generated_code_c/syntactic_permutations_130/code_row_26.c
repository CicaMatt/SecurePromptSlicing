#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    struct Environment {
        const char *name;
        void *template;
    };
    
    struct Request {
        const char *name;
    };
    
    struct Response {
        int status_code;
        const char *body;
    };
    
    struct Response render_response_from_env(struct Environment env) {
        struct Request request = {};
        request.name = "John Doe";
        
        struct Response response = {};
        response.status_code = 200;
        char *body = malloc(1024);
        sprintf(body, "%s %s", env.template, request.name);
        response.body = body;
        
        return response;
    }
    
    struct Response home(struct Environment env) {
        return render_response_from_env(env);
    }