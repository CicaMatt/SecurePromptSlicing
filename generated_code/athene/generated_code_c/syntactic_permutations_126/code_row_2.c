#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 100
#define BUFFER_SIZE 1024

void http_hello_page(int client_fd) {
    char username[MAX_USERNAME_LEN] = "";
    char outputbuf[BUFFER_SIZE] = "";

    // Read the request body (username)
    int n = read(client_fd, username, MAX_USERNAME_LEN - 1);
    if (n > 0) {
        username[n] = '\0'; // Null-terminate the string
    }

    // Construct the response body (HTML page)
    snprintf(outputbuf, BUFFER_SIZE, 
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Connection: close\r\n"
             "\r\n"
             "<html><head><title>Hello Page</title></head><body>"
             "<h1>Hello, %s!</h1>"
             "</body></html>", username);

    // Write the response body to the response stream
    write(client_fd, outputbuf, strlen(outputbuf));

    // Close the response stream
    close(client_fd);
}