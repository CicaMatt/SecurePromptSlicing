#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256] = "";
    int in_username = 0;

    while (fgets(buffer, sizeof(buffer), request)) {
        if (in_username && strlen(buffer) < 3) break; // End of username
        if (!in_username && strncmp("username=", buffer, 9) == 0) {
            in_username = 1;
            strncat(username, buffer + 9, sizeof(username) - 1);
        } else if (in_username) {
            strncat(username, buffer, sizeof(username) - strlen(username) - 1);
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", username);
}