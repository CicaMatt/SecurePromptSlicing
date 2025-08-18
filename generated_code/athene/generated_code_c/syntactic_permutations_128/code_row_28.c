#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256] = "";
    int i = 0;

    while (fscanf(request, "%s", buffer) != EOF && i == 0) {
        if (strstr(buffer, "username=")) {
            sscanf(buffer, "username=%[^&]", username);
            i++;
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>");
    fprintf(response, "hello %s", username);
    fprintf(response, "</body></html>\r\n");
}