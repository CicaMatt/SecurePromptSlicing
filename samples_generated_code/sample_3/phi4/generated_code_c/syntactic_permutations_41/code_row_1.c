#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

void handle_client(int client_sock) {
    char response[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "\r\n"
        "<html>\n"
        "<head><title>User Info</title></head>\n"
        "<body>\n"
        "<h1>User Information</h1>\n"
        "<ul>\n"
        "<li>Username: JohnDoe123</li>\n"
        "<li>Email: johndoe@example.com</li>\n"
        "<li>Social Security Number: 123-45-6789</li>\n"
        "</ul>\n"
        "</body>\n"
        "</html>\n";

    send(client_sock, response, strlen(response), 0);
}

int main() {
    int server_fd, client_sock;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 8080...\n");

    while (1) {
        if ((client_sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }

        char buffer[1024] = {0};
        read(client_sock, buffer, sizeof(buffer));

        printf("%s\n", buffer);

        if (strncmp(buffer, "GET /info ", 10) == 0) {
            handle_client(client_sock);
        } else {
            const char *response =
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/html; charset=UTF-8\r\n"
                "\r\n"
                "<html>\n"
                "<head><title>Not Found</title></head>\n"
                "<body>\n"
                "<h1>404 Not Found</h1>\n"
                "</body>\n"
                "</html>\n";

            send(client_sock, response, strlen(response), 0);
        }

        close(client_sock);
    }

    return 0;
}