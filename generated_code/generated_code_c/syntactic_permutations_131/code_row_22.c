#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    typedef struct {
      char *name;
    } Request;
    
    typedef struct {
      char *template;
    } Environment;
    
    Response* render_response_from_env(Environment *env) {
        // get name parameter from user request
        Request *req = (Request*)malloc(sizeof(Request));
        req->name = "John";
    
        // get template from environment
        char *template = env->template;
    
        // render the template with the name parameter
        int buf_size = 256;
        char *rendered_template = (char*)malloc(buf_size);
        snprintf(rendered_template, buf_size - 1, template, req->name);
    
        // return a response with the rendered template
        Response *res = (Response*)malloc(sizeof(Response));
        res->body = rendered_template;
        return res;
    }
    
    int main() {
        Environment *env = (Environment*)malloc(sizeof(Environment));
        env->template = "<html><p>Hello, %s!</p></html>";
    
        Response *res = render_response_from_env(env);
        printf("%s\n", res->body);
    }