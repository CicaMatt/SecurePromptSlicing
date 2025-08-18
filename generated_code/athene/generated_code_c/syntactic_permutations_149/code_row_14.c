#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 100
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;

    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        if (strncmp(buffer, "POST /post", 9) == 0) {
            char username[100], message[500];
            sscanf(buffer, "%*s %*s HTTP/1.1\r\n%*[^:]: %*[\r]\nContent-Length: %*d\r\n\r\nusername=%[^&]&message=%[^\r]", username, message);

            // Insert message into the database (mock implementation)
            printf("Inserting message from user '%s': '%s'\n", username, message);

            // Redirect to /
            const char *response = "HTTP/1.1 302 Found\r\nLocation: /\r\nContent-Length: 0\r\n\r\n";
            send(client_socket, response, strlen(response), 0);
        } else if (strncmp(buffer, "GET /", 4) == 0) {
            // Display messages (mock implementation)
            const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Messages</h1>";
            send(client_socket, response, strlen(response), 0);

            // Mock database query to display messages
            printf("Displaying all messages...\n");
            const char *mock_messages = "<p>User1: Hello World!</p><p>User2: How are you?</p>";
            send(client_socket, mock_messages, strlen(mock_messages), 0);

            const char *end_response = "</body></html>";
            send(client_socket, end_response, strlen(end_response), 0);
        }

        if (bytes_received == 0) break;
    }
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Bind socket to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
        perror("Bind failed");
        return -1;
    }

    // Listen for incoming connections
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        return -1;
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    return 0;
}