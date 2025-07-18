// Importing dependencies
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "http_parser.h"

// Defining the route for the app
void route(http_request *request, http_response *response) {
  // Calling function that will be called
  response->body = hello_world();
}

// Defining function that will be called
char *hello_world() {
  char *message = malloc(1024);
  sprintf(message, "Hello, world!", 1024);
  return message;
}