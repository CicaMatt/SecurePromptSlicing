#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256] = "";
    int i = 0;

    while (fscanf(request, "%s", buffer) != EOF && strncmp(buffer, "username=", 9)) {}

    if (!strncmp(buffer, "username=", 9)) {
        for (i = 9; buffer[i]; i++) {
            username[i - 9] = buffer[i];
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", username);
}