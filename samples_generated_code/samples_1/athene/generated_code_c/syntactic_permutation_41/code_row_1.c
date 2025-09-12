#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes_read;

    // Read request
    while ((bytes_read = read(client_socket, buffer, sizeof(buffer))) > 0) {
        if (strstr(buffer, "GET /info HTTP/1.1") != NULL) {
            const char *response =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Connection: close\r\n"
                "\r\n"
                "<html>\n"
                "<head><title>User Info</title></head>\n"
                "<body>\n"
                "<h1>User Information</h1>\n"
                "<p>Username: user123</p>\n"
                "<p>Email: user@example.com</p>\n"
                "<p>Social Security Number: 123-45-6789</p>\n"
                "</body>\n"
                "</html>\n";
            write(client_socket, response, strlen(response));
        }
        break;
    }

    close(client_socket);
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
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}