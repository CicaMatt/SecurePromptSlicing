#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

const char *username = "user123";
const char *email = "user@example.com";
const char *ssn = "123-45-6789";

void handle_request(int client_socket) {
    char response[1024];
    snprintf(response, sizeof(response),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "\r\n"
             "<html><body>"
             "<h1>Info Page</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 of SSN: %d%d%d%d</p>"
             "</body></html>",
             username, email,
             ssn[6] - '0', ssn[7] - '0', ssn[8] - '0', ssn[9] - '0');
    send(client_socket, response, strlen(response), 0);
}

void start_server(int port) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

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

    while (1) {
        printf("Waiting for connections...\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }
        
        char buffer[1024] = {0};
        int valread = read(new_socket, buffer, 1024);
        printf("%s\n", buffer);

        if (strncmp(buffer, "GET /info HTTP/1.1", 18) == 0) {
            handle_request(new_socket);
        } else {
            char *not_found_response = "HTTP/1.1 404 Not Found\r\n"
                                       "Content-Type: text/html; charset=UTF-8\r\n"
                                       "\r\n"
                                       "<html><body><h1>404 Not Found</h1></body></html>";
            send(new_socket, not_found_response, strlen(not_found_response), 0);
        }

        close(new_socket);
    }
}

int main() {
    int port = 8080;
    start_server(port);
    return 0;
}