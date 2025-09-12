#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SESSION_SIZE 1024

typedef struct {
    char username[256];
    char email[256];
    char ssn[256];
} Session;

Session session = { .username = "user123", .email = "user@example.com", .ssn = "123-45-6789" };

void handle_request(const char *request) {
    if (strncmp(request, "GET /info HTTP/1.1\r\n", 20) == 0) {
        printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
        printf("Username: %s\nEmail: %s\nSSN: %s\n", session.username, session.email, session.ssn);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n");
        printf("Not found\n");
    }
}

int main() {
    char buffer[SESSION_SIZE];
    
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    int addrlen = sizeof(address);
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }
        
        ssize_t bytes_read = read(new_socket, buffer, SESSION_SIZE - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            handle_request(buffer);
        }

        close(new_socket);
    }

    return 0;
}