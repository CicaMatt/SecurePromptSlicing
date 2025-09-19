#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 4096

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_read > 0) {
        // Assuming the POST request is sent in a single read for simplicity
        printf("Received %d bytes\n", bytes_read);

        // Simple parsing to extract file content from HTTP POST data
        char *file_content_start = strstr(buffer, "\r\n\r\n");
        if (file_content_start != NULL) {
            file_content_start += 4; // Move past the \r\n\r\n

            FILE *file = fopen("uploads/uploaded_file", "wb");
            if (file == NULL) {
                perror("Failed to open file for writing");
                return;
            }

            fwrite(file_content_start, sizeof(char), bytes_read - (file_content_start - buffer), file);
            fclose(file);

            // Send a simple HTTP response
            char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nFile uploaded successfully.";
            send(client_socket, response, strlen(response), 0);
        } else {
            printf("No file content found in request.\n");
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind to a port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Create uploads directory if it doesn't exist
    mkdir("./uploads", 0777);

    printf("Server listening on port %d\n", PORT);

    while (1) {
        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        handle_request(client_socket);
    }

    return 0;
}