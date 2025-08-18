#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int is_valid_domain(const char *url, const char *domain) {
    size_t url_len = strlen(url);
    if (url_len <= 7 || strncmp(url, "http://", 7) != 0) return 0;
    url += 7; // Skip http://
    while (*url && *url != '/' && *url != ':') {
        if (strstr(url, domain) == url) return 1;
        url++;
    }
    return 0;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    read(client_socket, buffer, BUFFER_SIZE - 1);

    const char *redirect_path = "/redirect/";
    if (strstr(buffer, redirect_path)) {
        char *url_start = strstr(buffer, redirect_path) + strlen(redirect_path);
        char url[BUFFER_SIZE];
        sscanf(url_start, "%s", url);

        if (is_valid_domain(url, "example.com")) {
            char response[] = "HTTP/1.1 302 Found\r\nLocation: ";
            send(client_socket, response, strlen(response), 0);
            send(client_socket, url, strlen(url), 0);
            send(client_socket, "\r\n", 2, 0);
        } else {
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid URL domain.";
            send(client_socket, response, strlen(response), 0);
        }
    } else {
        const char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nRoute not found.";
        send(client_socket, response, strlen(response), 0);
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

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

    printf("Server listening on port %d\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}