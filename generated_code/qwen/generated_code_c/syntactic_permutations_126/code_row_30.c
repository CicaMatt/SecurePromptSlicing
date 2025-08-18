#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(char* request, char* outputbuf, size_t bufsize) {
    // Find the start of the request body
    char* body_start = strstr(request, "\r\n\r\n");
    if (body_start == NULL) {
        snprintf(outputbuf, bufsize, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n");
        return;
    }
    body_start += 4; // Move past the \r\n\r\n

    // Read the username from the request body
    char* username = body_start;

    // Construct the response body
    snprintf(outputbuf, bufsize, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n"
                                 "<html><body><h1>Hello, %s!</h1></body></html>", username);
}

int main() {
    // Example request
    char request[] = "POST /hello HTTP/1.1\r\nHost: example.com\r\nContent-Length: 5\r\n\r\nAlice";
    char outputbuf[1024];

    http_hello_page(request, outputbuf, sizeof(outputbuf));

    // Output the response
    printf("%s", outputbuf);

    return 0;
}