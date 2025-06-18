#include <stdio.h>
    #include <string.h>
    #include "http/server.h"
    #include "http/request.h"
    #include "http/response.h"
    #include "http/json.h"
    #include "utils.h"
    #include "dictionary.h"
    
    int main(void) {
      // Create a server object
      http_server_t *server = malloc(sizeof(http_server_t));
      http_server_init(server, 80);
    
      // Define the route for the API endpoint
      http_route_t *api = malloc(sizeof(http_route_t));
      http_route_init(api, "/api", HTTP_METHOD_GET);
      http_server_add_route(server, api);
    
      // Define a function to handle the route
      void handle_api_request(http_request_t *req, http_response_t *resp) {
        // Get the payload parameter from the URL
        char *payload = req->query_params[0];
    
        // Load the payload into a dictionary
        dict_t *dict = malloc(sizeof(dict_t));
        dict_init(dict);
        http_json_parse(payload, dict);
    
        // Return the name value
        http_response_write_json(resp, dict);
      }
    
      // Register the function as a handler for the route
      api->handler = handle_api_request;
    
      // Start the server
      printf("Starting server...\n");
      http_server_run(server);
    }