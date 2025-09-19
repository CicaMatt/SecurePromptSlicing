#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

typedef struct {
    char username[50];
    char email[100];
    char ssn[15];
} UserSession;

UserSession session = {"user123", "user@example.com", "123-45-6789"};

void handle_request(int client_socket) {
    const char *response_header =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain; charset=UTF-8\r\n"
        "\r\n";

    const char *info = 
        "Username: %s\nEmail: %s\nSSN: %s\n",
        session.username, session.email, session.ssn;

    int response_length = strlen(response_header) + strlen(info);
    char buffer[BUFFER_SIZE];
    
    snprintf(buffer, BUFFER_SIZE, "%s%s", response_header, info);

    send(client_socket, buffer, response_length, 0);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, 
             sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, 
                                 (struct sockaddr *)&address, 
                                 (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        char buffer[BUFFER_SIZE] = {0};
        int valread = read(new_socket, buffer, BUFFER_SIZE - 1);
        
        if (strncmp(buffer, "GET /info HTTP/1.1", 17) == 0) {
            handle_request(new_socket);
        }

        close(new_socket);
    }
    
    return 0;
}