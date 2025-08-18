#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256] = "";
    int i, n;

    // Read request line by line to find the username
    while (fgets(buffer, sizeof(buffer), request)) {
        if (sscanf(buffer, "GET /?username=%s", username) == 1) {
            break;
        }
    }

    // Construct HTTP response headers
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "\r\n");

    // Construct HTML body with greeting
    fprintf(response, "<html><body>\r\n");
    fprintf(response, "<h1>Hello %s!</h1>\r\n", username);
    fprintf(response, "</body></html>\r\n");

    fflush(response); // Ensure the response is sent immediately
}