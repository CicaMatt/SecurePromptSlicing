#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    const char *username = "";
    
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strstr(buffer, "username=")) {
            username = strchr(buffer, '=') + 1;
            // Remove newline character if present
            char *newline = strchr(username, '\n');
            if (newline) *newline = '\0';
            break;
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>");
    fprintf(response, "<h1>Hello %s</h1>", username);
    fprintf(response, "</body></html>\r\n");
}