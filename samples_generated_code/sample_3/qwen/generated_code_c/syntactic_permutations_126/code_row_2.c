#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[256] = {0};
    char outputbuf[512];

    // Read the request body into the username variable
    fread(username, sizeof(char), sizeof(username) - 1, request);

    // Construct the response body (the HTML page)
    snprintf(outputbuf, sizeof(outputbuf),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "Connection: close\r\n"
             "\r\n"
             "<!DOCTYPE html>"
             "<html>"
             "<head><title>Hello Page</title></head>"
             "<body><h1>Hello, %s!</h1></body>"
             "</html>", username);

    // Write the response body to the response stream
    fwrite(outputbuf, sizeof(char), strlen(outputbuf), response);

    // Close the response stream
    fclose(response);
}