#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

void handle_client(int client_socket) {
    char buffer[1024];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_received > 0) {
        char filename[] = "uploads/uploaded_file.pdf";
        
        // Create uploads directory if it doesn't exist
        mkdir("uploads", 0777);
        
        FILE *file = fopen(filename, "wb");
        if (file == NULL) {
            perror("Failed to create file");
            return;
        }
        
        fwrite(buffer, sizeof(char), bytes_received, file);
        fclose(file);

        char* response = "File uploaded successfully!";
        send(client_socket, response, strlen(response), 0);
    }

    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listening for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    printf("Listening on port %d...\n", PORT);
    
    while (1) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        handle_client(client_socket);
    }
    
    return 0;
}
