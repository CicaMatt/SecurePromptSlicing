// Importing dependencies
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "templates/home.html"

// Declaring structs for request and environment
typedef struct {
  char* name;
} Request;

typedef struct {
  const char** templates;
} Environment;

// Function to render response from environment
Response* render_response_from_env(Environment* env) {
  // Get template from environment
  const char* home_template = env->templates["home.html"];

  // Render the template with name parameter
  char name[100];
  sprintf(name, "World");
  char output[1024];
  sprintf(output, home_template, name);

  // Return response with rendered template
  Response* res = malloc(sizeof(Response));
  res->body = output;
  return res;
}

// Home function calls the render response from environment function
void home(Environment* env) {
  render_response_from_env(env);
}