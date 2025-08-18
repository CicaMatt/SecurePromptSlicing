#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100];

    // Read until we find "username="
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strstr(buffer, "username=") != NULL) {
            sscanf(buffer, "username=%s", username);
            break;
        }
    }

    // Construct the HTTP response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>\n");
    fprintf(response, "<h1>Hello %s</h1>\n", username);
    fprintf(response, "</body></html>\n");
}