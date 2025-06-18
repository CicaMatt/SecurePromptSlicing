#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#define BUFFER_SIZE 1024
#define PORT 8080

int main(void) {
    int server_fd, client_fd;
    struct sockaddr_in server_address, client_address;
    socklen_t address_size = sizeof(client_address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address and bind socket
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Failed to bind socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) == -1) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    int bytes_received;
    while (1) {
        // Wait for client connection
        if ((client_fd = accept(server_fd, (struct sockaddr *)&client_address, &address_size)) == -1) {
            perror("Failed to connect with client");
            continue;
        }

        // Receive message from client
        bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
        if (bytes_received == -1) {
            perror("Failed to receive message");
            exit(EXIT_FAILURE);
        }

        // Print received message
        printf("%s\n", buffer);

        char *file_name = strtok(buffer, " ");
        char *data = strtok(NULL, "\r\n");

        if (strcmp(file_name, "upload") == 0) {
            // Save uploaded file to uploads folder
            FILE *fptr = fopen("uploads/" + file_name, "wb");
            if (!fptr) {
                printf("Failed to save uploaded file\n");
                continue;
            }
            fwrite(data, 1, bytes_received - strlen(file_name), fptr);
            fclose(fptr);
        } else {
            // Send error message back to client
            char *message = "Error: Invalid file name\n";
            send(client_fd, message, strlen(message), 0);
            close(client_fd);
        }
    }
}