#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

void http_hello_page(const char *request_body) {
    char outputbuf[MAX_BUFFER_SIZE];
    
    // Read username from request body
    char username[256] = {0};
    strncpy(username, request_body, sizeof(username) - 1);

    // Construct the response HTML page
    snprintf(outputbuf, MAX_BUFFER_SIZE,
             "<html>\n"
             "<head><title>Hello Page</title></head>\n"
             "<body>\n"
             "<h1>Hello, %s!</h1>\n"
             "</body>\n"
             "</html>", username);

    // Write the response body to the response stream (stdout for this example)
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html; charset=UTF-8\r\n");
    printf("\r\n"); // End of headers
    printf("%s", outputbuf);
    
    // Close the response stream (in actual server code, this would be handled differently)
}

int main() {
    const char *request_body = "JohnDoe";  // Example request body
    http_hello_page(request_body);

    return 0;
}