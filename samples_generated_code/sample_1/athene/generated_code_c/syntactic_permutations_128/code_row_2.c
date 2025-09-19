#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100] = "";
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "username=", 9) == 0) {
            sscanf(buffer + 9, "%[^&]", username);
            break;
        }
    }
    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", username);
}