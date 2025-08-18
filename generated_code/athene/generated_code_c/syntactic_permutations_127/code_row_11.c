#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100];

    // Read request line by line until we find "username="
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strstr(buffer, "username=")) {
            sscanf(buffer, "username=%s", username);
            break;
        }
    }

    // Construct and send the HTTP response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", username);
}