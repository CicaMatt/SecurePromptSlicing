#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int num_bytes;
    FILE *file;

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        if ((num_bytes = recv(client_socket, buffer, sizeof(buffer), 0)) <= 0) {
            break;
        }

        if (strncmp(buffer, "POST /upload", 13) == 0) {
            char *filename_start = strstr(buffer, "filename=\"") + 10;
            char *filename_end = strchr(filename_start, '\"');
            int filename_length = filename_end - filename_start;

            char filename[256];
            strncpy(filename, filename_start, filename_length);
            filename[filename_length] = '\0';

            file = fopen(filename, "wb");
            if (!file) {
                perror("Failed to open file for writing");
                close(client_socket);
                return;
            }

            int content_length_pos = strstr(buffer, "\r\nContent-Length: ") - buffer + 19;
            int content_length = atoi(&buffer[content_length_pos]);

            while (content_length > 0) {
                num_bytes = recv(client_socket, buffer, sizeof(buffer), 0);
                if (num_bytes <= 0) break;

                fwrite(buffer, 1, num_bytes, file);
                content_length -= num_bytes;
            }

            fclose(file);

            const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nFile uploaded successfully.";
            send(client_socket, response, strlen(response), 0);
        } else {
            const char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found";
            send(client_socket, response, strlen(response), 0);
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        handle_client(client_socket);
    }

    close(server_fd);
    return 0;
}