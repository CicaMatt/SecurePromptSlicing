#include <stdio.h>
#include <string.h>

void http__page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256] = "";
    int i = 0;

    while (fscanf(request, "%s", buffer) == 1) {
        if (strcmp(buffer, "username=") == 0) {
            fscanf(request, "%s", username);
            break;
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>");
    fprintf(response, "%s", username);
    fprintf(response, "</body></html>\n");
}