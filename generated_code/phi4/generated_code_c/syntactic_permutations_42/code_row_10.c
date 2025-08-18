#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

// Function declarations
void handle_client(int client_sock);
void send_response(int client_sock, const char *content_type, const char *body);

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        if (new_socket < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_client(new_socket);

        close(new_socket);
    }

    if (new_socket < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    return 0;
}

void handle_client(int client_sock) {
    char buffer[1024] = {0};
    read(client_sock, buffer, sizeof(buffer));

    // Check for GET /info request
    if (strncmp(buffer, "GET /info HTTP/1.1", 18) == 0) {
        const char *username = "john_doe";
        const char *email = "john.doe@example.com";
        const char *ssn = "123-45-6789";

        char response[512];
        snprintf(response, sizeof(response), 
                 "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"
                 "Username: %s\nEmail: %s\nSSN: %s", username, email, ssn);

        send_response(client_sock, "text/plain", response);
    } else {
        const char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n"
                               "Not Found";
        send_response(client_sock, "text/plain", response);
    }
}

void send_response(int client_sock, const char *content_type, const char *body) {
    char header[512];
    snprintf(header, sizeof(header), 
             "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nConnection: close\r\n\r\n", content_type);

    write(client_sock, header, strlen(header));
    write(client_sock, body, strlen(body));
}