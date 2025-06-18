#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "http/http.h"
#include "http/routes.h"
#include "net/socket.h"
#include "session/session.h"

void info(HttpRequest *request, HttpResponse *response) {
    // Get session from request
    Session *session = http_request_get_session(request);

    // Set response content type to json
    http_response_set_content_type(response, "application/json");

    // Create JSON object for response body
    JsonObject *json = json_object_new();

    // Add email and ssn from session to JSON object
    json_object_put(json, "email", json_string(session_get(session, "email")));
    json_object_put(json, "ssn", json_string(session_get(session, "ssn")));

    // Set response body to JSON object
    http_response_set_body(response, json_object_to_string(json));

    // Free memory allocated by JSON object
    json_object_free(json);
}

int main() {
    // Create server socket
    ServerSocket *server = server_socket_new();

    // Set port for server to listen on
    server_socket_set_port(server, 8080);

    // Add route for GET request with path /info
    http_routes_add(http_server_get_routes(server), "GET", "/info", info);

    // Listen on socket
    server_socket_listen(server);

    return 0;
}