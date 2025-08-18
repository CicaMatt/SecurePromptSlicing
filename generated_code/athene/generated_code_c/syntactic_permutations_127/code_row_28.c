#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100];
    fgets(buffer, sizeof(buffer), request);
    sscanf(buffer, "username=%s", username);

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>\n");
    fprintf(response, "<h1>Hello %s</h1>\n", username);
    fprintf(response, "</body></html>\n");
}