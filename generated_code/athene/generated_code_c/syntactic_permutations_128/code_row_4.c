#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100] = "";
    int i;

    while (fgets(buffer, sizeof(buffer), request)) {
        if (sscanf(buffer, "GET /?username=%99[^&]", username) == 1) {
            break;
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>\n");
    fprintf(response, "Hello %s!\n", username);
    fprintf(response, "</body></html>\n");
}