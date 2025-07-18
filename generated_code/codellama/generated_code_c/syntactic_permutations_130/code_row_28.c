#include "http/cgi.h"
#include <stdlib.h>
#include <stdio.h>

// The home function
void home(struct Environment* env) {
    // Call the render_response_from_env with env variable
    return render_response_from_env(env);
}

// The render_response_from_env function
void render_response_from_env(struct Environment* env) {
    // Get name from request using the get_request_param function
    char* name = get_request_param("name", 4, env->req);
    // Get template using the get_template function
    char* tmpl = get_template(env);
    // Render the template with name variable
    render_template(tmpl, name);
    // Return response with rendered template
    return build_response(200, "OK", tmpl);
}