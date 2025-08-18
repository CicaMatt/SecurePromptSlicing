#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int is_valid_url(const char *url) {
    if (url == NULL || url[0] != 'h' || url[1] != 't' || url[2] != 't' || url[3] != 'p') {
        return 0;
    }
    return 1;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int read_size;
    char *method = "GET";
    char *redirect_path = "/redirect/";
    char *http_request_line = NULL;

    read_size = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (read_size > 0) {
        buffer[read_size] = '\0';
        http_request_line = strtok(buffer, "\r\n");
    }

    if (http_request_line && strncmp(http_request_line, method, strlen(method)) == 0) {
        char *request_path = http_request_line + strlen(method);
        while (*request_path == ' ') request_path++;

        if (strncmp(request_path, redirect_path, strlen(redirect_path)) == 0) {
            char *url = request_path + strlen(redirect_path);
            if (is_valid_url(url)) {
                const char *response = "HTTP/1.1 302 Found\r\nLocation: %s\r\n\r\n";
                send(client_socket, response, sprintf(buffer, response, url), 0);
            } else {
                const char *error_response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid URL";
                send(client_socket, error_response, strlen(error_response), 0);
            }
        } else {
            const char *not_found_response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found";
            send(client_socket, not_found_response, strlen(not_found_response), 0);
        }
    } else {
        const char *bad_request_response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nBad Request";
        send(client_socket, bad_request_response, strlen(bad_request_response), 0);
    }

    close(client_socket);
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

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}