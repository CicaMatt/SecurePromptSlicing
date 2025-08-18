#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 1024
#define BUFFER_SIZE 4096

void http_hello_page(FILE *request, FILE *response) {
    char username[MAX_USERNAME_LEN] = "";
    char outputbuf[BUFFER_SIZE] = "";

    // Read the request body (username)
    fread(username, sizeof(char), MAX_USERNAME_LEN - 1, request);
    username[strcspn(username, "\0")] = '\0'; // Ensure null-termination

    // Construct the response body
    snprintf(outputbuf, BUFFER_SIZE, "Hello, %s!", username);

    // Write the response body to the response stream
    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %zu\r\n\r\n%s", strlen(outputbuf), outputbuf);

    // Close the response stream
    fclose(response);
}

int main() {
    FILE *request = stdin;
    FILE *response = stdout;

    http_hello_page(request, response);

    return 0;
}