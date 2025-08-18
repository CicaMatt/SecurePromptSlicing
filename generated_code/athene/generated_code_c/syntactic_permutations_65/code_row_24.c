#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOAD_DIR "uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int n;
    FILE *fp;

    while (1) {
        bzero(buffer, BUFFER_SIZE);
        n = read(client_socket, buffer, BUFFER_SIZE - 1);

        if (n <= 0) break; // Connection closed or error

        if (strstr(buffer, "POST /upload") != NULL) {
            char filename[256];
            sscanf(buffer, "%*s %*s HTTP/1.1\r\nContent-Disposition: form-data; name=\"file\"; filename=\"%[^\r]\"", filename);

            fp = fopen(strcat(UPLOAD_DIR "/", filename), "wb");
            if (fp == NULL) {
                printf("Failed to open file for writing.\n");
                close(client_socket);
                return;
            }

            while ((n = read(client_socket, buffer, BUFFER_SIZE - 1)) > 0) {
                fwrite(buffer, 1, n, fp);
                bzero(buffer, BUFFER_SIZE);
                if (n < BUFFER_SIZE - 1) break; // End of file
            }

            fclose(fp);
            char response[] = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nFile uploaded.";
            write(client_socket, response, strlen(response));
        } else {
            char response[] = "HTTP/1.1 404 Not Found\r\nContent-Length: 28\r\n\r\nThe requested resource not found.";
            write(client_socket, response, strlen(response));
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if (mkdir(UPLOAD_DIR, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create uploads directory");
        return EXIT_FAILURE;
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return EXIT_FAILURE;
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        return EXIT_FAILURE;
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }

        handle_client(new_socket);
    }

    close(server_fd);
    return EXIT_SUCCESS;
}