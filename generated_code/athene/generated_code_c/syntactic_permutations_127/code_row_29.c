#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100] = "";
    int in_username = 0;
    
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strstr(buffer, "username=")) {
            const char *start = strchr(buffer, '=') + 1;
            int len = strcspn(start, "&\r\n");
            strncpy(username, start, len);
            username[len] = '\0';
            in_username = 1;
            break;
        }
    }

    if (in_username) {
        fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
        fprintf(response, "<html><body>Hello %s</body></html>", username);
    } else {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n");
        fprintf(response, "Username not found in request.");
    }
}