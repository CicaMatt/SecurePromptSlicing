#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080

void handle_request(const char *request) {
    printf("Received request:\n%s\n", request);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    
    printf("Server listening on port %d\n", PORT);

    while (1) {
        addr_size = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
        
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }
        
        memset(buffer, 0, 1024);
        read(client_socket, buffer, 1023);

        handle_request(buffer);

        char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nHello from C Web Server!";
        write(client_socket, response, strlen(response));

        close(client_socket);
    }

    close(server_socket);
    return 0;
}


To compile this program, use:


gcc -o c_web_server your_file_name.c


Then run the server with:


./c_web_server


This code sets up a basic TCP server on port 8080 and responds to HTTP requests with a simple "Hello from C Web Server!" message. Make sure you have the necessary permissions and environment to bind to low-numbered ports (like 8080).