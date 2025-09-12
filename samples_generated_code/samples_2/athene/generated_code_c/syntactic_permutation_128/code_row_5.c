#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char name[256] = "";
    
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncasecmp(buffer, "GET /", 5) == 0) {
            sscanf(buffer, "GET /%[^ ]", name);
            break;
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", name);
}