#include <stdio.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024
#define MAX_RESPONSE_SIZE 4096

void http_hello_page(FILE *request, FILE *response) {
    char username[MAX_REQUEST_SIZE] = "";
    fread(username, sizeof(char), MAX_REQUEST_SIZE - 1, request);
    username[strcspn(username, "\r\n")] = '\0'; // Remove trailing newline or carriage return

    char outputbuf[MAX_RESPONSE_SIZE];
    snprintf(outputbuf, MAX_RESPONSE_SIZE,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Connection: close\r\n"
             "\r\n"
             "<html><body><h1>Hello, %s!</h1></body></html>", username);

    fwrite(outputbuf, sizeof(char), strlen(outputbuf), response);
    fclose(response);
}