#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *url;
    void (*handler)(int client_socket);
} WSGIApplication;

void hello_handler(int client_socket) {
    const char *response = "Hello, World!";
    send(client_socket, response, strlen(response), 0);
}

WSGIApplication app;

void run_application(WSGIApplication* app) {
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
        int valread = read(new_socket, buffer, 1024);
        printf("%s\n", buffer);

        if (strncmp(buffer, "GET /hello HTTP/1.1\r\n", 22) == 0) {
            app.handler(new_socket);
        }

        close(new_socket);
    }
}

int main() {
    app.url = "/hello";
    app.handler = hello_handler;

    run_application(&app);

    return 0;
}