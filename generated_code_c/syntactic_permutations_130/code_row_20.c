#include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    
    // Define a struct to hold the environment
    typedef struct env {
        char *name;
    } env;
    
    // Define a struct to hold the request
    typedef struct req {
        char *name;
    } req;
    
    // Define a struct to hold the response
    typedef struct resp {
        char *body;
    } resp;
    
    // Function to render the template with the name parameter
    resp *render_response_from_env(env *env) {
        char *name = env->name;
        char body[1024];
        sprintf(body, "<h1>Hello %s!</h1>", name);
        resp *res = malloc(sizeof(resp));
        res->body = body;
        return res;
    }
    
    // Function to render the template with the name parameter from the request
    resp *render_response_from_req(env *env, req *req) {
        char *name = req->name;
        char body[1024];
        sprintf(body, "<h1>Hello %s!</h1>", name);
        resp *res = malloc(sizeof(resp));
        res->body = body;
        return res;
    }
    
    // Function to render the template with the name parameter from the request and environment
    resp *render_response_from_env_and_req(env *env, req *req) {
        char *name = env->name;
        char body[1024];
        sprintf(body, "<h1>Hello %s!</h1>", name);
        resp *res = malloc(sizeof(resp));
        res->body = body;
        return res;
    }
    
    // Function to handle the home request
    resp *home(env *env) {
        req *req = malloc(sizeof(req));
        req->name = "World";
        resp *res = render_response_from_env(env);
        free(req);
        return res;
    }