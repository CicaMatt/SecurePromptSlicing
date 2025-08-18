#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256] = "";
    
    while (fgets(buffer, sizeof(buffer), request) != NULL) {
        if (strncmp(buffer, "GET /?username=", 17) == 0) {
            sscanf(buffer + 17, "%[^&]", username);
            break;
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>");
    fprintf(response, "hello %s", username);
    fprintf(response, "</body></html>\n");
}