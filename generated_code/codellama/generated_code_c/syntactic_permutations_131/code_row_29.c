#include <stdio.h>
#include <stdlib.h>
#include "templates/index.html.tmpl"
#include "templates/base.html.tmpl"
#include "render_response_from_env.h"

void render_response_from_env(environment *env, char *name){
    //get template from env
    char *template = (char *) malloc(strlen(env->tmpl) + 1);
    strcpy(template, env->tmpl);

    //render template with name paramter from request
    char *rendered_html = (char *) malloc(strlen(template) + 1);
    sprintf(rendered_html, template, name);

    //return response with rendered template
    return response{200, rendered_html};
}

response home(environment *env){
    char *name = (char *) malloc(strlen("World") + 1);
    strcpy(name, "World");
    render_response_from_env(env, name);
    return response{200, "Hello World!"};
}