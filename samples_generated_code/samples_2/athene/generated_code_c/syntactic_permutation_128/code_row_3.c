#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100] = "";
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "username=", 9) == 0) {
            sscanf(buffer + 9, "%s", username);
            break;
        }
    }
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "hello %s", username);
}