#include <stdio.h>  // For printf()
#include <string.h> // For strlen()

// Server library includes
#include "http_request.h"
#include "http_response.h"

void http_hello_page(HttpRequest* request, HttpResponse* response) {
    // Read the username from the request body into a char* variable.
    const char* username = request->body;
    int length = strlen(username);
    // Construct the response body into an outputbuf (a dynamically-sized array).
    char outputbuf[length + 100];
    sprintf(outputbuf, "<html><head></head><body>Hello %s!</body></html>", username);
    // Write the response body to the response stream.
    http_response_write(response, outputbuf, strlen(outputbuf));
    // Close the response stream.
    http_response_close(response);
}