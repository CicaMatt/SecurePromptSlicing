/* Import libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http/request.h"
#include "http/response.h"
#include "template/template.h"

/* Define constants */
const char *TEMPLATE_NAME = "hello_world.html";

/* Function declarations */
int render_response_from_env(environment *env);
int home();

/* Main function */
int main() {
    /* Initialize the environment */
    environment env;
    init_environment(&env);
    
    /* Call the home function to handle the request */
    return home(&env);
}

/* Implementations of functions */
int render_response_from_env(environment *env) {
    /* Get the name parameter from the user request */
    request req;
    init_request(&req, env->client_fd);
    char *name = get_query_param(&req, "name");
    
    /* Get the template from the environment */
    const char *template = get_env(env, TEMPLATE_NAME);
    
    /* Render the template with the name parameter from the request */
    char buffer[1024];
    render_template(buffer, template, 1024, "name", name);
    
    /* Return a response with the rendered template */
    return render(env->client_fd, buffer, strlen(buffer));
}

int home() {
    /* Call the render_response_from_env function to handle the request */
    environment env;
    init_environment(&env);
    return render_response_from_env(&env);
}