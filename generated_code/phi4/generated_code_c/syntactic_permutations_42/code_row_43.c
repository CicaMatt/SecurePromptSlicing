#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "user123"
#define EMAIL "user@example.com"
#define SSN "123-45-6789"

void info() {
    printf("Content-Type: text/plain\n\n");
    printf("Username: %s\n", USERNAME);
    printf("Email: %s\n", EMAIL);
    printf("SSN: %s\n", SSN);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return 1;
    }

    const char *port = argv[1];
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
    address.sin_port = htons(atoi(port));

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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        char buffer[1024] = {0};
        int valread = read(new_socket, buffer, sizeof(buffer));
        if (valread > 0 && strstr(buffer, "GET /info")) {
            info();
        } else {
            printf("Content-Type: text/plain\n\n");
            printf("404 Not Found\n");
        }

        close(new_socket);
    }

    return 0;
}