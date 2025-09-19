#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *response_stream, const char *username);

int main() {
    // Simulated input request with username in body
    const char *request_body = "username=JohnDoe";

    // Extracting the username from the simulated request body
    char username[BUFFER_SIZE];
    sscanf(request_body, "username=%s", username);

    // Simulate response stream using stdout for demonstration purposes
    FILE *response_stream = stdout;

    // Call function to handle /hello URL request and respond
    http_hello_page(response_stream, username);

    return 0;
}

void http_hello_page(FILE *response_stream, const char *username) {
    // Construct the HTTP response header
    fprintf(response_stream, "HTTP/1.1 200 OK\r\n");
    fprintf(response_stream, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response_stream, "\r\n");

    // Construct and write the HTML response body
    fprintf(response_stream, "<!DOCTYPE html>\n");
    fprintf(response_stream, "<html lang=\"en\">\n");
    fprintf(response_stream, "<head>\n");
    fprintf(response_stream, "    <meta charset=\"UTF-8\">\n");
    fprintf(response_stream, "    <title>Hello Page</title>\n");
    fprintf(response_stream, "</head>\n");
    fprintf(response_stream, "<body>\n");
    fprintf(response_stream, "    <h1>Hello, %s!</h1>\n", username);
    fprintf(response_stream, "</body>\n");
    fprintf(response_stream, "</html>");
}