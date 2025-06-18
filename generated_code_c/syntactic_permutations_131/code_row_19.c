#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* render_response_from_env(const char* name, const char* template) {
    // TODO: Render the response using the template and name
}

const char* home(const char* env) {
    // Get the user request from the environment
    const char* name = get_name_from_request(env);

    // Render the response with the name parameter from the request
    const char* response = render_response_from_env(name, "<html><body>Hello {{name}}!</body></html>");

    return response;
}