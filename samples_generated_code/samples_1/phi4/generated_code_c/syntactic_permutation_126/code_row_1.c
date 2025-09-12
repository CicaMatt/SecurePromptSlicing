#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(const char *request_body, char *response_stream) {
    // Read the username from the request body
    const char *username = request_body;

    // Construct the response HTML page with the username
    snprintf(response_stream, BUFFER_SIZE,
             "<html>\n"
             "  <head><title>Hello</title></head>\n"
             "  <body>\n"
             "    <h1>Hello, %s!</h1>\n"
             "  </body>\n"
             "</html>",
             username);

    // Simulate writing the response body to the response stream
    printf("%s\n", response_stream);

    // Simulate closing the response stream (in actual use-case, this would be handled by server framework)
}

int main() {
    char request_body[] = "Alice";
    char response_stream[BUFFER_SIZE];

    http_hello_page(request_body, response_stream);

    return 0;
}