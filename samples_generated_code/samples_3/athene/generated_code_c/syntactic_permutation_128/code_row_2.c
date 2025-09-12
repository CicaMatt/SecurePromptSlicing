#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256] = "";
    int found = 0;

    while (fgets(buffer, sizeof(buffer), request)) {
        if (strstr(buffer, "username=")) {
            sscanf(buffer, "%*[^=]=%s", username);
            found = 1;
            break;
        }
    }

    if (!found) {
        strcpy(username, "Anonymous");
    }

    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    fprintf(response, "<html><body><h1>Hello %s</h1></body></html>", username);
}