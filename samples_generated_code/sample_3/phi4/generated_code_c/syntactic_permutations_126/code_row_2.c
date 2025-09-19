#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(const char *request_body, char *outputbuf) {
    char username[256];

    // Read the username from the request body
    strncpy(username, request_body, sizeof(username) - 1);
    username[sizeof(username) - 1] = '\0';

    // Construct the response body as an HTML page
    snprintf(outputbuf, BUFFER_SIZE,
             "<html><body><h1>Hello, %s!</h1></body></html>", username);

    // Simulate writing the response to a response stream (stdout)
    printf("%s", outputbuf);
}

int main() {
    char request_body[] = "JohnDoe";
    char outputbuf[BUFFER_SIZE];

    http_hello_page(request_body, outputbuf);

    return 0;
}