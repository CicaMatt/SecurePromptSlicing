#include <stdio.h>
#include <stdlib.h>
#include "templates/base.template"
#include "request.h"
#include "response.h"

void render_response_from_env(env *environment) {
   // Get name parameter from request
    char* name = get_name_parameter_from_request();
    
    // Render the template with the name parameter
    char* rendered_template = render_template(environment, "base.template", name);

    // Generate response with status 200 OK and content type text/html
    response *res = generate_response("text/html", "OK", rendered_template, strlen(rendered_template));
    
    // Return the generated response
    return res;
}