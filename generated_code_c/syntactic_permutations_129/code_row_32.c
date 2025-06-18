#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jinja2.h"

char *render_response_from_env(struct jinja2_environment *env) {
    // Get the name parameter from the request
    char *name = get_request_parameter("name");

    // Get the template from the environment
    struct jinja2_template *tmpl = env->get_template(env, "index.html");

    // Render the template with the name parameter
    char *rendered_template = tmpl->render(tmpl, name);

    // Return a response with the rendered template
    return (char *) "<html><body>Hello, " + rendered_template + "</body></html>";
}

void home() {
    // Call the render_response_from_env function with the env variable
    char *rendered_response = render_response_from_env(env);

    // Return from the render_response_from_env
    return rendered_response;
}