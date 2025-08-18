#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];

    // Read request line (GET /user?username=...)
    fgets(buffer, sizeof(buffer), request);

    // Extract the username from the query string
    sscanf(buffer, "GET /user?username=%s", username);

    // Construct HTTP response header and body
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", username);
}