#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define PORT 8080
#define MAX_FILENAME_LENGTH 256
#define BUFFER_SIZE 1024

void send_response(int client_socket, const char *status, const char *content_type, const char *body) {
    char response[1024];
    snprintf(response, sizeof(response),
             "HTTP/1.1 %s\r\n"
             "Content-Type: %s\r\n"
             "Connection: close\r\n"
             "\r\n"
             "%s", status, content_type, body);
    send(client_socket, response, strlen(response), 0);
}

void handle_upload(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    char filename[MAX_FILENAME_LENGTH] = "uploaded_file_";
    char *ext = ".bin";
    strncat(filename, ext, MAX_FILENAME_LENGTH - strlen(filename));

    int file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_fd == -1) {
        send_response(client_socket, "500 Internal Server Error", "text/plain", "Failed to create file");
        return;
    }

    while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        write(file_fd, buffer, bytes_read);
    }

    close(file_fd);
    send_response(client_socket, "200 OK", "text/plain", "File uploaded successfully");
}

void handle_request(int client_socket) {
    char request[BUFFER_SIZE];
    if (recv(client_socket, request, sizeof(request), 0) <= 0) {
        return;
    }

    if (strstr(request, "POST /upload HTTP/1.1")) {
        handle_upload(client_socket);
    } else {
        send_response(client_socket, "404 Not Found", "text/plain", "Not Found");
    }
}

int main() {
    int server_fd, client_socket;
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

    printf("Server listening on port %d\n", PORT);

    while ((client_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) >= 0) {
        handle_request(client_socket);
        close(client_socket);
    }

    perror("accept");
    close(server_fd);
    return EXIT_FAILURE;
}