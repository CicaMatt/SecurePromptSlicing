#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *response_stream, const char *request_body) {
    // Extract username from request body
    char username[BUFFER_SIZE] = {0};
    if (sscanf(request_body, "username=%[^\r\n]", username) != 1) {
        strcpy(username, "unknown");
    }

    // Construct response body
    const char *response_header =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "\r\n";
    
    const char *html_content =
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<head>\n"
        "<meta charset=\"UTF-8\">\n"
        "<title>Hello</title>\n"
        "</head>\n"
        "<body>\n"
        "<h1>Hello, %s!</h1>\n"
        "</body>\n"
        "</html>";

    char response_body[BUFFER_SIZE * 2];
    snprintf(response_body, sizeof(response_body), html_content, username);

    // Write response header and body to the response stream
    fprintf(response_stream, "%s%s", response_header, response_body);
}

int main() {
    // Simulate receiving a request with username in the body
    const char *request_body = "username=JohnDoe";

    // Open a file to simulate the response stream (stdout can be used in real scenarios)
    FILE *response_stream = stdout;

    // Call the function to handle the /hello URL request
    http_hello_page(response_stream, request_body);

    // Close the response stream
    fclose(response_stream);

    return 0;
}