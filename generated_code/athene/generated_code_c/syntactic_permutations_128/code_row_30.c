#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256] = "";
    int i = 0;

    while (fscanf(request, "%s", buffer) != EOF) {
        if (strcmp(buffer, "username=") == 0) {
            fscanf(request, "%s", username);
            for (i = 0; username[i]; ++i) {
                if (username[i] == '&' || username[i] == ';') {
                    username[i] = '\0';
                    break;
                }
            }
            break;
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", username);
}