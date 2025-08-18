#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[100];
    fscanf(request, "username=%s", username);

    const char* response_start = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    fprintf(response, "%s", response_start);
    fprintf(response, "Hello %s", username);
}