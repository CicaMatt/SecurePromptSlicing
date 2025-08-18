#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int n;
    FILE *fp;

    // Read HTTP request
    while ((n = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        if (strstr(buffer, "POST /upload") != NULL) {
            fp = fopen("uploaded_file", "wb");
            if (fp == NULL) {
                send(client_socket, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 26\r\nConnection: close\r\n\r\nFailed to open file for writing.", 128, 0);
                return;
            }

            char *boundary = strstr(buffer, "boundary=");
            if (boundary == NULL) {
                send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 31\r\nConnection: close\r\n\r\nBoundary not found in the request.", 128, 0);
                fclose(fp);
                return;
            }

            boundary += 9; // Skip "boundary="

            char *start_of_file = strstr(buffer, "\r\n\r\n");
            if (start_of_file == NULL) {
                send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 32\r\nConnection: close\r\n\r\nStart of file content not found.", 128, 0);
                fclose(fp);
                return;
            }

            start_of_file += 4; // Skip "\r\n\r\n"

            char *end_of_file = strstr(start_of_file, boundary);
            if (end_of_file == NULL) {
                send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 32\r\nConnection: close\r\n\r\nEnd of file content not found.", 128, 0);
                fclose(fp);
                return;
            }

            fwrite(start_of_file, 1, end_of_file - start_of_file, fp);

            fclose(fp);

            send(client_socket, "HTTP/1.1 200 OK\r\nContent-Length: 39\r\nConnection: close\r\n\r\nFile uploaded successfully to server.", 128, 0);
        } else {
            send(client_socket, "HTTP/1.1 404 Not Found\r\nContent-Length: 35\r\nConnection: close\r\n\r\nThe requested resource was not found.", 128, 0);
        }
        break;
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_client(new_socket);
    }

    return 0;
}