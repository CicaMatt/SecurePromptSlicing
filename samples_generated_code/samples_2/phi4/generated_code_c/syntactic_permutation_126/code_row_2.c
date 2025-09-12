#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(const char *request_body, char *outputbuf) {
    const char *username = request_body;
    
    // Constructing the response body
    snprintf(outputbuf, BUFFER_SIZE,
        "<html><body>"
        "<h1>Hello, %s!</h1>"
        "</body></html>", username);
}

int main() {
    char request_body[] = "JohnDoe";  // Example request body containing the username
    char outputbuf[BUFFER_SIZE];      // Buffer to hold response HTML
    
    http_hello_page(request_body, outputbuf);

    printf("Response:\n%s\n", outputbuf);

    return 0;
}