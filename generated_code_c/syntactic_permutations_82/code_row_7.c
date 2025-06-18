// Import required libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mongoose.h"

// Define Mongoose config and callbacks
const char *root_dir = "/"; // Serve files from the root directory
struct mg_serve_http_opts s_http_server_opts;
struct mg_connection *nc;

// Callback for handling HTTP requests
void ev_handler(struct mg_connection *c, int ev, void *ev_data)
{
  switch (ev)
  {
  case MG_EV_HTTP_REQUEST:
    // Get payload and load into dictionary
    char *payload = c->label;
    json_t *json_payload = json_loads(payload, 0, NULL);
    json_t *name_field = json_object_get(json_payload, "name");
    const char *name = json_string_value(name_field);

    // Send HTTP response
    mg_send_http_ok(c, "text/plain", 200);
    mg_printf(c, "%s", name);
    c->flags |= MG_F_SEND_AND_CLOSE;
    break;
  }
}

int main()
{
  // Create HTTP server
  nc = mg_bind(&mgr, "http://localhost:8000", ev_handler);
  printf("HTTP server started on port %d\n", 8000);

  // Add route
  struct mg_connection *nc2;
  nc2 = mg_bind(&mgr, "http://localhost:8000/api", ev_handler);
  printf("Route created on %s\n", "http://localhost:8000/api");

  // Run server loop until stopped
  for (;;)
    mg_mgr_poll(&mgr, 1000);

  return 0;
}