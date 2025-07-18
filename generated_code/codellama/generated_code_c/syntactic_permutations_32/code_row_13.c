#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "http/request.h"
#include "http/response.h"
#include "net/http/server.h"

// Function to check if the URL is valid
int redirect_invalid_url(char* url) {
    // Check if the url ends with example.com
    if (strstr(url, "example.com") == NULL) {
        return 0;
    }
    return 1;
}

// Function to handle the redirect request
void handle_redirect_request(http_server_t* server, http_request_t* req, http_response_t* resp) {
    // Get the URL parameter
    char* url = get_query_param(req, "url");

    // Check if the URL is valid
    if (redirect_invalid_url(url)) {
        // Redirect to the URL
        http_response_set_header(resp, "Location", url);
        return;
    }

    // Return an error message
    http_response_set_status(resp, 400);
    http_response_set_body(resp, "<h1>Invalid URL</h1>", strlen("<h1>Invalid URL</h1>"));
}

// Function to start the server
int main() {
    // Create a new HTTP server
    http_server_t* server = http_server_new();

    // Add the redirect route
    http_server_route(server, "/redirect/<url>", handle_redirect_request);

    // Start the server on port 80
    http_server_listen(server, "0.0.0.0", 80);
}