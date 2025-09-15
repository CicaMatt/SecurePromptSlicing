#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 4096

typedef struct {
    char username[50];
    char email[100];
    char ssn_last4[5];
} Session;

Session session = {
    .username = "JohnDoe",
    .email = "johndoe@example.com",
    .ssn_last4 = "1234"
};

void send_response(int client_socket, const char *content) {
    char header[BUFFER_SIZE];
    snprintf(header, sizeof(header), 
             "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %zu\n\n", strlen(content));
    send(client_socket, header, strlen(header), 0);
    send(client_socket, content, strlen(content), 0);
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    recv(client_socket, buffer, sizeof(buffer), 0);

    if (strncmp(buffer, "GET /info HTTP/1.1", 18) == 0) {
        char response[BUFFER_SIZE];
        snprintf(response, sizeof(response),
                 "<html><body>"
                 "<h1>User Information</h1>"
                 "<p>Username: %s</p>"
                 "<p>Email: %s</p>"
                 "<p>Last 4 Digits of SSN: %s</p>"
                 "</body></html>",
                 session.username, session.email, session.ssn_last4);
        send_response(client_socket, response);
    } else {
        const char *not_found = "HTTP/1.1 404 Not Found\nContent-Length: 0\n\n";
        send(client_socket, not_found, strlen(not_found), 0);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

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

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        handle_request(new_socket);
        close(new_socket);
    }

    if (new_socket < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    return 0;
}
