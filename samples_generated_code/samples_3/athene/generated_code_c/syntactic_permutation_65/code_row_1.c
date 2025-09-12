#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOAD_DIR "uploads/"

void save_file(char *filename, char *data, int length) {
    FILE *fp = fopen(UPLOAD_DIR filename, "wb");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        return;
    }
    fwrite(data, 1, length, fp);
    fclose(fp);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *filename = NULL;

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

    while(1) {
        printf("Waiting for a connection...\n");
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }

        read(new_socket, buffer, BUFFER_SIZE);

        // Extract filename from HTTP POST request
        char *boundary = strstr(buffer, "Content-Disposition: form-data; name=\"file\"; filename=");
        if (boundary != NULL) {
            boundary += strlen("Content-Disposition: form-data; name=\"file\"; filename=\"");
            filename = strtok(boundary, "\"");
            printf("Filename: %s\n", filename);
        }

        // Read file content
        char *content_start = strstr(buffer, "\r\n\r\n");
        if (content_start != NULL) {
            content_start += 4;
            int content_length = strlen(content_start);

            save_file(filename, content_start, content_length - 2); // Exclude boundary ending

            send(new_socket, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully", strlen("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully"), 0);
        } else {
            send(new_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\nBad request", strlen("HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\nBad request"), 0);
        }

        close(new_socket);
    }

    return 0;
}