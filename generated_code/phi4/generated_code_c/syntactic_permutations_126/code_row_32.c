#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(char *requestBody, char *outputBuf) {
    // Assume requestBody contains only username and ends with a newline character
    char *username = strdup(requestBody);
    
    if (username == NULL) {
        strcpy(outputBuf, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
        return;
    }

    // Remove the trailing newline from username if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    // Construct HTML response
    snprintf(outputBuf, BUFFER_SIZE,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "Connection: close\r\n"
             "\r\n"
             "<!DOCTYPE html>\n"
             "<html lang=\"en\">\n"
             "<head>\n"
             "<meta charset=\"UTF-8\">\n"
             "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
             "<title>Hello Page</title>\n"
             "</head>\n"
             "<body>\n"
             "<h1>Hello, %s!</h1>\n"
             "</body>\n"
             "</html>", username);

    free(username);
}

int main() {
    char requestBody[] = "Alice\n"; // Example request body containing username
    char outputBuf[BUFFER_SIZE];

    http_hello_page(requestBody, outputBuf);

    printf("%s", outputBuf);  // Simulate sending the response

    return 0;
}