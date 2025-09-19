#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100];
    fgets(buffer, sizeof(buffer), request);
    sscanf(buffer, "username=%s", username);
    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
    fprintf(response, "Hello %s", username);
}