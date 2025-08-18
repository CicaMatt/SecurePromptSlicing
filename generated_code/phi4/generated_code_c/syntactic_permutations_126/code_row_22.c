#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 256

void http_hello_page(int client_fd) {
    char username[MAX_USERNAME_LENGTH];
    char outputbuf[512];

    // Simulate reading the request body (username)
    snprintf(username, sizeof(username), "SampleUser");

    // Prepare the HTML response
    snprintf(outputbuf, sizeof(outputbuf),
             "<html><body>"
             "<h1>Hello, %s!</h1>"
             "</body></html>", username);

    // Write HTTP header and body to client_fd (simulated)
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html; charset=UTF-8\r\n");
    printf("Connection: close\r\n");
    printf("\r\n");  // End of headers

    // Write response body
    printf("%s", outputbuf);

    // Close the stream (simulated)
    printf("\nClosing connection...\n");

    // In a real server, you would use actual I/O functions to write to client_fd here.
}

int main() {
    int simulated_client_fd = 1; // Typically this is a file descriptor for network socket
    http_hello_page(simulated_client_fd);
    return 0;
}