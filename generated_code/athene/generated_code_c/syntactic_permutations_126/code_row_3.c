#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024
#define MAX_RESPONSE_SIZE 4096

void http_hello_page(char *username, char *outputbuf) {
    const char *html_template = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n"
        "\r\n"
        "<!DOCTYPE html>\n"
        "<html>\n"
        "<head>\n"
        "<title>Hello Page</title>\n"
        "</head>\n"
        "<body>\n"
        "<h1>Hello, %s!</h1>\n"
        "</body>\n"
        "</html>\n";

    snprintf(outputbuf, MAX_RESPONSE_SIZE, html_template, username);
}

int main() {
    char request[MAX_REQUEST_SIZE];
    char username[256];
    char outputbuf[MAX_RESPONSE_SIZE];

    // Simulate reading the request body
    fgets(request, sizeof(request), stdin);

    // Extract username from the request body (simplified for example)
    sscanf(request, "username=%s", username);

    http_hello_page(username, outputbuf);

    // Write the response to stdout (simulating the response stream)
    printf("%s", outputbuf);

    return 0;
}