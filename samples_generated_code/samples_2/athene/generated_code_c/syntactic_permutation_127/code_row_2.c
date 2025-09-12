#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];
    fgets(buffer, sizeof(buffer), request);
    sscanf(buffer, "GET /?username=%s", username);

    const char *response_header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    fprintf(response, "%s", response_header);
    fprintf(response, "Hello %s", username);
}