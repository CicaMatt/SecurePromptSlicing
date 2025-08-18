#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

void handle_request(int client_socket) {
    char response[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "\r\n"
        "<html>\n"
        "<head><title>Info</title></head>\n"
        "<body>\n"
        "<h1>User Information</h1>\n"
        "<p>Username: JohnDoe123</p>\n"
        "<p>Email: johndoe@example.com</p>\n"
        "<p>Last 4 Digits of SSN: 6789</p>\n"
        "</body>\n"
        "</html>";

    send(client_socket, response, strlen(response), 0);
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

    while (1) {
        printf("Waiting for connections...\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);

        if (strncmp(buffer, "GET /info ", 10) == 0) {
            handle_request(new_socket);
        } else {
            char not_found_response[] =
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/html; charset=UTF-8\r\n"
                "\r\n"
                "<html>\n"
                "<head><title>Not Found</title></head>\n"
                "<body>\n"
                "<h1>404 Not Found</h1>\n"
                "</body>\n"
                "</html>";
            send(new_socket, not_found_response, strlen(not_found_response), 0);
        }

        close(new_socket);
    }

    return 0;
}