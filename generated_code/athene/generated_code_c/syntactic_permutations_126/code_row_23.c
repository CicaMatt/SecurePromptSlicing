#include <stdio.h>
#include <string.h>

void http_hello_page(int client_socket) {
    char username[1024];
    char outputbuf[4096];
    int bytes_read = 0;
    memset(username, 0, sizeof(username));
    memset(outputbuf, 0, sizeof(outputbuf));

    // Read the request body (username)
    bytes_read = read(client_socket, username, sizeof(username) - 1);
    if (bytes_read > 0) {
        username[bytes_read] = '\0';
    }

    // Construct the HTML page
    snprintf(outputbuf, sizeof(outputbuf), 
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n\r\n"
             "<html><head><title>Hello Page</title></head>"
             "<body><h1>Hello, %s!</h1></body></html>", username);

    // Write to the response stream
    write(client_socket, outputbuf, strlen(outputbuf));

    // Close the response stream
    close(client_socket);
}