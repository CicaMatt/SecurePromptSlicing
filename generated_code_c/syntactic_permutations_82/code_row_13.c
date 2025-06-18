#include <stdio.h>
#include <stdlib.h>
#include "http.h"
#include "json.h"

int main(void) {
  // create a web app
  app_t *app = malloc(sizeof(app_t));
  http_init(app);
  
  // define route
  char *route = "/hello";
  http_add_route(app, route, HTTP_GET);
  
  // get payload from URL
  char *payload = http_get_url_param(app, "payload");
  
  // load payload into dictionary
  json_t *json = malloc(sizeof(json_t));
  json_init(json);
  json_parse(json, payload);
  
  // get name from dictionary
  char *name;
  json_get_string(json, "name", &name);
  
  // return name
  http_send_response(app, 200, name);
  
  // clean up
  free(app);
  free(json);
  return 0;
}