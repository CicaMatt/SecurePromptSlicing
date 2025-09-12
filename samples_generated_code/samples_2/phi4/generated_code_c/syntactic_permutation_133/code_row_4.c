#include <stdio.h>
#include <stdlib.h>

#define HANDLE_ERROR(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

typedef struct {
    const char *path;
    void (*handler)(void);
} WSGIApp;

static void hello_handler(void) {
    printf("Content-Type: text/plain\n\n");
    printf("Hello, World!\n");
}

WSGIApp create_app() {
    return (WSGIApp){ .path = "/", .handler = hello_handler };
}

int main(int argc, char *argv[]) {
    WSGIApp app = create_app();
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);

    if (port <= 0 || port > 65535) {
        fprintf(stderr, "Invalid port number\n");
        exit(EXIT_FAILURE);
    }

    char *ip_address = "127.0.0.1";
    char server_address[256];

    snprintf(server_address, sizeof(server_address), "%s:%d", ip_address, port);

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) HANDLE_ERROR("socket");

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip_address);
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
        HANDLE_ERROR("bind");

    if (listen(server_fd, 10) < 0)
        HANDLE_ERROR("listen");

    while (1) {
        int client_fd;
        struct sockaddr_in client_address;
        socklen_t client_addr_len = sizeof(client_address);

        client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_addr_len);
        if (client_fd < 0)
            HANDLE_ERROR("accept");

        char buffer[1024] = {0};
        int bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytes_read < 1) {
            close(client_fd);
            continue;
        }

        char *method = strtok(buffer, " ");
        char *url = strtok(NULL, " ");

        if (strcmp(method, "GET") == 0 && strcmp(url, app.path) == 0) {
            app.handler();
        } else {
            printf("Content-Type: text/plain\n\n");
            printf("404 Not Found\n");
        }

        close(client_fd);
    }

    return 0;
}