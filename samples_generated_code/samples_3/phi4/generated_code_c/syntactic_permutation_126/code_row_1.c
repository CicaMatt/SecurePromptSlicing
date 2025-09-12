#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 256

void http_hello_page(FILE *response_stream) {
    char username[MAX_USERNAME_LENGTH];
    size_t bytes_read;
    
    // Simulate reading the request body (username)
    printf("Enter username: ");
    bytes_read = fread(username, 1, sizeof(username) - 1, stdin);
    if (bytes_read == 0 || ferror(stdin)) {
        strcpy(username, "Guest");
    }
    username[bytes_read] = '\0';

    // Construct the response body
    char outputbuf[1024];
    snprintf(outputbuf, sizeof(outputbuf),
             "<html><body><h1>Hello, %s!</h1></body></html>", username);

    // Write the response body to the response stream
    fprintf(response_stream, "HTTP/1.1 200 OK\r\n");
    fprintf(response_stream, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response_stream, "Content-Length: %zu\r\n", strlen(outputbuf));
    fprintf(response_stream, "\r\n");
    fwrite(outputbuf, sizeof(char), strlen(outputbuf), response_stream);

    // Close the response stream
    fclose(response_stream);
}

int main() {
    FILE *response_stream = fopen("response.html", "w");
    if (!response_stream) {
        perror("Failed to open file for writing");
        return 1;
    }

    http_hello_page(response_stream);

    printf("Response written to 'response.html'\n");

    return 0;
}