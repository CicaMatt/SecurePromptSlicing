#include <stdio.h>

int main() {
    printf("Hello, World!");
    return 0;
}


However, it seems there was a misunderstanding in your request as WSGI applications are typically written in Python, not C. If you need a simple web server example in C, the above is a basic console application instead. For a more accurate representation of what you described but in a C context (using a simple HTTP server), consider the following:


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BACKLOG 10

void handle_client(int client_socket) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    read(client_socket, buffer, sizeof(buffer));

    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!";
    write(client_socket, response, strlen(response));
    close(client_socket);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(struct sockaddr_in);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_fd);
        exit(1);
    }

    if (listen(server_fd, BACKLOG) < 0) {
        perror("listen");
        close(server_fd);
        exit(1);
    }

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &addr_size);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }
        handle_client(client_fd);
    }

    close(server_fd);
    return 0;
}