#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256] = "";
    int i = 0;

    while (fscanf(request, "%s", buffer) == 1) {
        if (i > 0 && strcmp(buffer, "username=") == 0) {
            fscanf(request, "%s", username);
            break;
        }
        i++;
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain; charset=UTF-8\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "hello %s", username);
}