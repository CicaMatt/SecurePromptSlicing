#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[1024] = {0};
    char outputbuf[2048];

    // Read the request body (username)
    fgets(username, sizeof(username), request);

    // Construct the response body
    snprintf(outputbuf, sizeof(outputbuf),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "Connection: close\r\n"
             "\r\n"
             "<!DOCTYPE html>"
             "<html><head><title>Hello Page</title></head>"
             "<body><h1>Hello, %s!</h1></body></html>", username);

    // Write the response body to the response stream
    fputs(outputbuf, response);

    // Close the response stream
    fclose(response);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (!request || !response) {
        perror("Failed to open files");
        exit(EXIT_FAILURE);
    }

    http_hello_page(request, response);

    fclose(request);
    return 0;
}