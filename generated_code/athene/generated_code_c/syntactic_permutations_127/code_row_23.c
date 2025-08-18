#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100];
    memset(username, 0, sizeof(username));

    // Read the request line by line to find the username
    while (fgets(buffer, sizeof(buffer), request)) {
        if (sscanf(buffer, "username=%99s", username) == 1) {
            break;
        }
    }

    // Construct the HTTP response header and body
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", username);
}