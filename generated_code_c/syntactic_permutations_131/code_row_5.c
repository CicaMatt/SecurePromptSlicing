#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "env.h"
#include "render_template.h"
 
typedef struct {
    char *name;
} Request;
 
Response* render_response_from_env(Env env) {
    // Get the name parameter from the user request
    Request req = get_request(env);
    printf("Got request: %s\n", req.name);
    char *template = get_template(env);
    // Render the template with the name parameter from the request
    char *body = render_template(template, req.name);
    Response *response = make_response();
    set_response_body(response, body);
    return response;
}
 
Response* home(Env env) {
    // Call the render_response_from_env function with the env variable
    Response *response = render_response_from_env(env);
    return response;
}