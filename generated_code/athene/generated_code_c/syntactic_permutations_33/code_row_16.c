#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int is_valid_url(const char *url) {
    if (url == NULL || url[0] != 'h' || url[1] != 't' || url[2] != 't' || url[3] != 'p') return 0;
    // Basic check for http:// or https://
    const char *http = "http://";
    const char *https = "https://";
    if (strncmp(url, http, strlen(http)) == 0) return 1;
    if (strncmp(url, https, strlen(https)) == 0) return 1;
    return 0;
}

void redirect_invalid_url(int client_socket, const char *url) {
    if (is_valid_url(url)) {
        char response[BUFFER_SIZE];
        snprintf(response, BUFFER_SIZE, "HTTP/1.1 302 Found\r\nLocation: %s\r\nContent-Length: 0\r\n\r\n", url);
        send(client_socket, response, strlen(response), 0);
    } else {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 23\r\n\r\nInvalid URL provided.\n";
        send(client_socket, response, strlen(response), 0);
    }
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        char *url = NULL;
        if (sscanf(buffer, "GET /?url=%s HTTP/1.1", &url) == 1) {
            redirect_invalid_url(client_socket, url);
        } else {
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 25\r\n\r\nInvalid request format.\n";
            send(client_socket, response, strlen(response), 0);
        }
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