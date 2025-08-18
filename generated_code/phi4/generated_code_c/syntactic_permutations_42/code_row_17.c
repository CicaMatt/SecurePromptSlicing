#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

#define PORT 8080

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session session = {
    .username = "john_doe",
    .email = "john.doe@example.com",
    .ssn = "123-45-6789"
};

void handle_request(int client_socket) {
    const char *response_header =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Connection: close\r\n"
        "\r\n";

    char response_body[256];
    snprintf(response_body, sizeof(response_body),
             "Username: %s\nEmail: %s\nSSN: %s",
             session.username, session.email, session.ssn);

    const char *response = response_header;
    send(client_socket, response, strlen(response), 0);
    send(client_socket, "\n", 1, 0); // newline between header and body
    send(client_socket, response_body, strlen(response_body), 0);
}

void start_server() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
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

    while ((new_socket = accept(server_fd, 
                                (struct sockaddr *)&address, 
                                (socklen_t*)&addrlen))) {
        handle_request(new_socket);
        close(new_socket);
    }
}

int main() {
    start_server();
    return 0;
}