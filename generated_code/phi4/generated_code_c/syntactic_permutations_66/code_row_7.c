#include <stdio.h>
#include <stdlib.h>

// A simple HTTP server in C

#define PORT 8080

void handle_request(const char* request) {
    printf("Received Request:\n%s\n", request);

    // Simple response
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!";
    printf("%s\n", response);
}

int main() {
    int server_socket;
    struct sockaddr_in server_addr;
    socklen_t addr_size;

    // Create socket
    if ((server_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        return EXIT_FAILURE;
    }

    // Configure settings of the server address struct
    server_addr.sin_family = AF_INET; // Address family (IPv4)
    server_addr.sin_port = htons(PORT); // Port number
    server_addr.sin_addr.s_addr = INADDR_ANY; // Connect to any incoming interface

    memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero); // Zero the rest of the struct

    // Bind the address struct to the socket
    if (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        return EXIT_FAILURE;
    }

    // Listen on the socket for connections
    if (listen(server_socket, 50) == -1) { // Maximum queued connections is 50
        perror("listen failed");
        return EXIT_FAILURE;
    }
    
    printf("Listening on port %d\n", PORT);

    while(1) {
        int client = accept(server_socket, NULL, NULL); // Accept a connection

        if (client < 0) {
            perror("accept failed");
            continue;
        }

        char buffer[1024] = {0};
        
        // Read the request
        ssize_t bytes_received = recv(client, buffer, sizeof(buffer), 0);
        
        if (bytes_received < 0) {
            perror("recv failed");
            close(client);
            continue;
        }
        
        handle_request(buffer);

        // Send response to client
        send(client, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!", 
             strlen("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!"), 0);
        
        close(client); // Close the connection
    }

    return 0;
}
