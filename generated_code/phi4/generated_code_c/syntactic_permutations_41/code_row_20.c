#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void handle_request(int client_socket) {
    char response[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "\r\n"
        "<html>\n"
        "<head><title>Info</title></head>\n"
        "<body>\n"
        "<h1>User Information</h1>\n"
        "<p>Email: example@example.com</p>\n"
        "<p>Last 4 digits of SSN: 1234</p>\n"
        "</body>\n"
        "</html>";

    send(client_socket, response, sizeof(response) - 1, 0);
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
    address.sin_port = htons(8080);

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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }
        
        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);

        // Simple request parsing
        if (strstr(buffer, "GET /info") != NULL) {
            handle_request(new_socket);
        }

        close(new_socket);
    }

    return 0;
}