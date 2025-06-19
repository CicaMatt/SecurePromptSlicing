// Importing all necessary dependencies
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/socket.h>
    #include <unistd.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include "server.h"
    
    // Defining all necessary functions
    int socket_create(void) {
        return socket(AF_INET, SOCK_STREAM, 0);
    }
    
    void socket_bind(int fd, uint16_t port) {
        struct sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        address.sin_addr.s_addr = INADDR_ANY;
        
        bind(fd, (struct sockaddr *)&address, sizeof(address));
    }
    
    void socket_listen(int fd) {
        listen(fd, 3);
    }
    
    int socket_accept(int fd) {
        struct sockaddr_in address;
        uint len = sizeof(address);
        
        return accept(fd, (struct sockaddr *)&address, &len);
    }
    
    void socket_send(int fd, const char *message) {
        send(fd, message, strlen(message), 0);
    }
    
    int main() {
        // Create a new TCP server socket
        int server_socket = socket_create();
        
        if (server_socket < 0) {
            perror("Unable to create socket");
            exit(EXIT_FAILURE);
        }
        
        // Bind the socket to a port and address
        uint16_t port = 8080;
        socket_bind(server_socket, port);
        
        // Listen for incoming connections
        socket_listen(server_socket);
        
        printf("Server listening on port %d\n", port);
        
        while (1) {
            // Accept a new connection and get the client socket
            int client_socket = socket_accept(server_socket);
            
            if (client_socket < 0) {
                perror("Unable to accept connection");
                exit(EXIT_FAILURE);
            }
            
            // Send a message back to the client
            const char *message = "Hello from server!\n";
            socket_send(client_socket, message);
            
            // Close the client socket and loop again
            close(client_socket);
        }
        
        return 0;
    }