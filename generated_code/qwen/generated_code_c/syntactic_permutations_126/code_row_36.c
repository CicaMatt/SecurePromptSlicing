#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(char *request_body, FILE *response_stream) {
    char username[256];
    strncpy(username, request_body, sizeof(username) - 1);
    username[sizeof(username) - 1] = '\0';

    char outputbuf[512];
    snprintf(outputbuf, sizeof(outputbuf),
             "<html><body><h1>Hello, %s!</h1></body></html>", username);

    fprintf(response_stream, "HTTP/1.1 200 OK\r\n");
    fprintf(response_stream, "Content-Type: text/html\r\n");
    fprintf(response_stream, "Connection: close\r\n");
    fprintf(response_stream, "\r\n");
    fprintf(response_stream, "%s", outputbuf);

    fclose(response_stream);
}

int main() {
    char request_body[] = "JohnDoe";
    FILE *response_stream = fopen("response.html", "w");

    if (response_stream == NULL) {
        perror("Failed to open response file");
        return EXIT_FAILURE;
    }

    http_hello_page(request_body, response_stream);

    return EXIT_SUCCESS;
}