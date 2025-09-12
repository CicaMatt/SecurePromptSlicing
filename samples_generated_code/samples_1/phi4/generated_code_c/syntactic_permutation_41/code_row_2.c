#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8080

void handle_request(int client_socket) {
    char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
                      "<html><body>"
                      "<h1>User Information</h1>"
                      "<p>Username: user12345</p>"
                      "<p>Email: user@example.com</p>"
                      "<p>Last 4 Digits of SSN: ****6789</p>"
                      "</body></html>";

    send(client_socket, response, strlen(response), 0);
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

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
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

    printf("Server is listening on port %d...\n", PORT);

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        if (new_socket < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);

        if (strstr(buffer, "GET /info")) {
            handle_request(new_socket);
        } else {
            const char *not_found_response = 
                "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n"
                "<html><body><h1>404 Not Found</h1></body></html>";

            send(new_socket, not_found_response, strlen(not_found_response), 0);
        }

        close(new_socket);
    }

    if (new_socket < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    return 0;
}