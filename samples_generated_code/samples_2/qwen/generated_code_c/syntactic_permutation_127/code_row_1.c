#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];

    while (fgets(buffer, sizeof(buffer), request)) {
        if (sscanf(buffer, "username=%255s", username) == 1) {
            fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", username);
            break;
        }
    }
}