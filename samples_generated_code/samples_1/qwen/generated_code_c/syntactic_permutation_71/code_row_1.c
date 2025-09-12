#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int valread = read(client_socket, buffer, BUFFER_SIZE);
    if (valread <= 0) {
        close(client_socket);
        return;
    }

    const char *file_upload_start = "Content-Disposition: form-data; name=\"file\"; filename=\"";
    const char *content_type = "\r\nContent-Type: ";
    const char *boundary = "--";
    const char *end_boundary = "\r\n\r\n";

    char *start = strstr(buffer, file_upload_start);
    if (start == NULL) {
        send(client_socket, "HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Type: text/plain\r\n\r\nInvalid request", strlen("HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Type: text/plain\r\n\r\nInvalid request"));
        close(client_socket);
        return;
    }

    start += strlen(file_upload_start);
    char *filename = start;
    char *end = strchr(start, '"');
    if (end == NULL) {
        send(client_socket, "HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Type: text/plain\r\n\r\nInvalid request", strlen("HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Type: text/plain\r\n\r\nInvalid request"));
        close(client_socket);
        return;
    }
    *end = '\0';

    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        send(client_socket, "HTTP/1.1 500 Internal Server Error\r\nConnection: close\r\nContent-Type: text/plain\r\n\r\nFailed to open file", strlen("HTTP/1.1 500 Internal Server Error\r\nConnection: close\r\nContent-Type: text/plain\r\n\r\nFailed to open file"));
        close(client_socket);
        return;
    }

    end += strlen(content_type);
    char *newline = strstr(end, "\r\n");
    if (newline == NULL) {
        fclose(file);
        send(client_socket, "HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Type: text/plain\r\n\r\nInvalid request", strlen("HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Type: text/plain\r\n\r\nInvalid request"));
        close(client_socket);
        return;
    }
    *newline = '\0';

    newline += strlen(end_boundary);
    fwrite(newline, 1, BUFFER_SIZE - (newline - buffer), file);

    while ((valread = read(client_socket, buffer, BUFFER_SIZE)) > 0) {
        end = strstr(buffer, boundary);
        if (end != NULL) {
            *end = '\0';
        }
        fwrite(buffer, 1, valread - (end ? strlen(boundary) : 0), file);
        if (end != NULL) {
            break;
        }
    }

    fclose(file);
    send(client_socket, "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Type: text/plain\r\n\r\nFile uploaded successfully", strlen("HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Type: text/plain\r\n\r\nFile uploaded successfully"));
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
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) >= 0) {
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}