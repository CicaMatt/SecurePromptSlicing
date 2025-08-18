#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
    if (bytes_read <= 0) {
        close(client_socket);
        return;
    }
    buffer[bytes_read] = '\0';

    const char *http_method = "GET ";
    const char *payload_param = "payload=";
    const char *create_type = "&type=Create";
    
    if (strstr(buffer, http_method)) {
        char *start = strstr(buffer, payload_param);
        if (start) {
            start += strlen(payload_param);
            char *end = strchr(start, ' ');
            if (!end) end = strchr(start, '&');
            if (end) {
                size_t length = end - start;
                char payload[length + 1];
                strncpy(payload, start, length);
                payload[length] = '\0';

                if (strstr(buffer, create_type)) {
                    const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nError: Type Create is not allowed.";
                    write(client_socket, response, strlen(response));
                } else {
                    // Handle other types or no type specified
                    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nPayload received.";
                    write(client_socket, response, strlen(response));
                }
            } else {
                const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nError: Payload parameter is malformed.";
                write(client_socket, response, strlen(response));
            }
        } else {
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nError: Payload parameter not found.";
            write(client_socket, response, strlen(response));
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

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
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) > 0) {
        handle_client(new_socket);
    }

    return 0;
}