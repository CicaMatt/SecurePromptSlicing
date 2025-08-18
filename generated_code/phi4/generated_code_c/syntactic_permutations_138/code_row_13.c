#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(const char *request) {
    const char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nHello, World!";
    
    // Simulating request handling logic
    if (strncmp(request, "GET / ", 6) == 0) {
        printf("%s", response);
    } else {
        const char *not_found = "HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nNot Found";
        printf("%s", not_found);
    }
}

void start_server() {
    char buffer[BUFFER_SIZE];
    
    // Simulating a server listening for connections
    printf("Server started. Listening on port 8080...\n");
    
    while (1) {
        printf("\nEnter HTTP request (or 'exit' to stop):\n> ");
        
        if (!fgets(buffer, BUFFER_SIZE, stdin)) break;
        
        if (strncmp(buffer, "exit", 4) == 0) break;
        
        handle_request(buffer);
    }
    
    printf("Server stopped.\n");
}

int main() {
    start_server();
    return 0;
}


Note: This code simulates a very basic HTTP server in C. It doesn't actually create a network socket or listen for incoming connections, as that would require more complex networking code involving system calls and libraries like `socket` on POSIX systems.