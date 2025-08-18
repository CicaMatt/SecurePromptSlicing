#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    char username[100];

    // Read the request line (GET /?username=...)
    fgets(buffer, sizeof(buffer), request);

    // Extract the username from the query string
    sscanf(buffer, "GET /?username=%s", username);

    // Construct the HTTP response header
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "\r\n");

    // Construct the HTML body with a greeting
    fprintf(response, "<html><body>");
    fprintf(response, "Hello %s", username);
    fprintf(response, "</body></html>");

    fflush(response);
}