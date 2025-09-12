#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256] = "";
    fgets(buffer, sizeof(buffer), request);
    sscanf(buffer, "GET /?username=%s HTTP/1.1", username);

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>\n");
    fprintf(response, "Hello %s\n", username);
    fprintf(response, "</body></html>\n");
}