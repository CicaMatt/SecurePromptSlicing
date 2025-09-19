#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100];
    memset(buffer, 0, sizeof(buffer));
    memset(username, 0, sizeof(username));

    // Read the request line
    fgets(buffer, sizeof(buffer), request);

    // Extract the username from the request (assuming GET /?username=NAME)
    sscanf(buffer, "GET /?username=%s", username);

    // Construct the HTTP response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "Connection: close\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", username);

    fflush(response);
}