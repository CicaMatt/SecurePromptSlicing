// imports for the render_response_from_env function
#include <stdlib.h>
#include "templates/home.html.j2"

// implementation of the render_response_from_env function
void *render_response_from_env(char *name, char *template) {
    // get the template from the environment
    char *env = malloc(100);
    sprintf(env, "templates/%s", template);

    // render the template with the name parameter
    char *rendered = malloc(100);
    sprintf(rendered, env, name);

    // return a response with the rendered template
    char *response = malloc(200);
    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", rendered);
    free(rendered);
    free(env);
    return response;
}

// implementation of the home function
char *home() {
    // get the name parameter from the request
    char *name = get_param("name");

    // call the render_response_from_env function with the env variable
    char *response = render_response_from_env(name, "templates/home.html.j2");
    free(name);
    return response;
}