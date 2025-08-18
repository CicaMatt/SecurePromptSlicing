#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100] = "";
    int i = 0;

    // Read request line by line to find the username
    while (fgets(buffer, sizeof(buffer), request)) {
        if (sscanf(buffer, "username=%s", username) == 1) {
            break;
        }
    }

    // Construct HTTP response header
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "\r\n");

    // Construct HTML content with hello message
    fprintf(response, "<html><body>");
    fprintf(response, "hello %s", username);
    fprintf(response, "</body></html>");
}