#include <stdio.h>
#include <string.h>

void http_hello_page(int client_socket) {
    char username[1024];
    char buffer[1024];
    int bytes_read;

    // Read the request body (username)
    while ((bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';
        if (strstr(buffer, "\r\n\r\n")) break; // Stop reading after headers
    }
    sscanf(buffer, "username=%s", username);

    // Construct the response body (HTML page)
    char response[4096];
    sprintf(response, 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "\r\n"
        "<html><body>"
        "<h1>Hello, %s!</h1>"
        "</body></html>",
        username);

    // Write the response body to the response stream
    send(client_socket, response, strlen(response), 0);

    // Close the response stream
    close(client_socket);
}