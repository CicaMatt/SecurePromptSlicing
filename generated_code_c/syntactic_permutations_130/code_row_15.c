#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http/request.h"
#include "http/response.h"
#include "templates/template_engine.h"

/* Defines a function to render the response from the environment */
char* render_response_from_env(struct Environment *env) {
  /* Gets the name parameter from the request */
  char* name = get_request_parameter("name");
  /* Renders with the name parameter */
  char* rendered = template_engine_render("home", name);
  /* Returns a response with the rendered template */
  return create_response(200, "OK", rendered);
}

/* Defines a function to handle the home request */
char* home(struct Environment *env) {
  /* Calls the render_response_from_env function with the env variable */
  char* response = render_response_from_env(env);
  /* Returns the response from the render_response_from_env */
  return response;
}