#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(const char *request) {
    printf("HTTP/1.0 200 OK\n");
    printf("Content-Type: text/html; charset=UTF-8\n\n");
    printf("<html>\n<head><title>Simple Web App</title></head>\n<body>\n");
    if (strstr(request, "GET / ")) {
        printf("<h1>Welcome to the Simple Web Application!</h1>");
        printf("<p>This is a basic example of a web application written in C.</p>");
    } else {
        printf("<h1>404 Not Found</h1>");
    }
    printf("</body>\n</html>\n");
}

int main() {
    char buffer[BUFFER_SIZE];
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    // Create a socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    // Bind the socket to a port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 8080...\n");

    while (1) {
        // Accept a connection
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len)) < 0) {
            perror("Accept failed");
            continue;
        }
        
        // Receive the request from client
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received < 0) {
            perror("Receive failed");
            close(client_socket);
            continue;
        }

        // Handle the request and send response
        handle_request(buffer);

        // Close the client socket
        close(client_socket);
    }

    // Close server socket
    close(server_socket);
    
    return 0;
}


To compile and run this C code, you'll need a Linux environment with GCC installed. Use the following commands:


gcc -o simple_web_app simple_web_app.c
./simple_web_app


After running the program, visit `http://localhost:8080/` in a web browser to see your simple web application in action.