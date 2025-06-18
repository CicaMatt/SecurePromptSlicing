#include <stdio.h>
#include <stdlib.h>
#include "http/request.h"
#include "templates/renderer.h"

// The home function is called to handle GET requests made to the root URL.
int home(struct request *req, struct response *res) {
    // Get the environment variable from the request.
    struct env_var *env = req->env;
    
    // Get the name parameter from the request.
    char *name = get_param_value(req, "name");
    
    // Get the template from the environment.
    char *template = get_template(env, "index.html");
    
    // Render the template with the name parameter.
    struct string_buffer *output = render_template(template, name);
    
    // Return a response with the rendered template.
    return respond(res, 200, output->data, "text/html");
}