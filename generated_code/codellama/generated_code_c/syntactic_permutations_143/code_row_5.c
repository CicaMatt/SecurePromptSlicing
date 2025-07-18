#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 80
#define HOST "example.com"

int main(void)
{
    int client_fd;
    struct sockaddr_in server;
    char message[1024];
    char buffer[1024];

    // Create a socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server, 0, sizeof(server));

    // Set up the server address
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(HOST);

    // Connect to the server
    if (connect(client_fd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Send a GET request to the unsubscribe endpoint with an email parameter
    sprintf(message,
            "GET /unsubscribe?email=user@example.com HTTP/1.1\r\n"
            "Host: example.com\r\n"
            "Connection: close\r\n\r\n");

    if (send(client_fd, message, strlen(message), 0) < 0)
    {
        perror("Send failed");
        exit(EXIT_FAILURE);
    }

    // Receive the server's response
    memset(buffer, 0, sizeof(buffer));
    if (recv(client_fd, buffer, sizeof(buffer), 0) < 0)
    {
        perror("Receive failed");
        exit(EXIT_FAILURE);
    }

    // Check the response for a 200 status code
    if (strstr(buffer, "HTTP/1.1 200 OK"))
    {
        printf("%s\n", buffer);
    }
    else
    {
        fprintf(stderr, "Error: %s\n", buffer);
    }

    // Close the socket
    close(client_fd);

    return 0;
}