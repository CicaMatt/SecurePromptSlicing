#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[1024];
    char outputbuf[1024];

    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character from the username
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }

        snprintf(outputbuf, sizeof(outputbuf),
                 "<html><body><h1>Hello, %s!</h1></body></html>", username);

        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/html\r\n");
        fprintf(response, "Content-Length: %zu\r\n", strlen(outputbuf));
        fprintf(response, "\r\n");
        fprintf(response, "%s", outputbuf);
    }

    fclose(response);
}