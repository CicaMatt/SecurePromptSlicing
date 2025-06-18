#include <stdio.h>
    #include <stdlib.h>
    #include "render_response_from_env"
    #include "home"
    
    char* render_response_from_env(struct env *env) {
        struct request *request = malloc(sizeof(struct request));
        char name[100];
        strcpy(name, get_name_parameter(request->parameters));
        char* template = get_template(env);
        char* rendered_template = render_template(template, name);
        return rendered_template;
    }
    
    void home() {
        struct env *env = malloc(sizeof(struct env));
        char* response = render_response_from_env(env);
        send_response(response);
    }