#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(char *username, char *outputbuf) {
    // Constructing HTML page in output buffer
    snprintf(outputbuf, BUFFER_SIZE,
        "<html><head><title>Hello</title></head>"
        "<body><h1>Hello, %s!</h1>"
        "<p>Welcome to the server.</p></body></html>", username);

    printf("Response Body: \n%s\n", outputbuf);
}

int main() {
    char username[100];
    char outputbuf[BUFFER_SIZE];

    // Simulating reading a username from an HTTP request
    strcpy(username, "JohnDoe");

    // Calling function to construct response body
    http_hello_page(username, outputbuf);

    return 0;
}