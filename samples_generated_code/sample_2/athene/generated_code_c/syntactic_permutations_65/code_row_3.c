#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOAD_DIR "./uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;
    FILE *fp;
    char filename[100];

    while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        if (strstr(buffer, "POST /upload") != NULL) {
            sscanf(buffer, "%*s %*s HTTP/1.1\r\n%*[^;]; filename=\"%[^\"]\"", filename);
            snprintf(buffer, sizeof(buffer), "%s/%s", UPLOAD_DIR, filename);
            fp = fopen(buffer, "wb");
            if (fp == NULL) {
                printf("Failed to open file for writing.\n");
                return;
            }
            while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
                fwrite(buffer, 1, bytes_read, fp);
                if (strstr(buffer, "\r\n\r\n") != NULL) break;
            }
            char content[BUFFER_SIZE];
            int content_length = 0;
            while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
                fwrite(buffer, 1, bytes_read, fp);
                content_length += bytes_read;
                if (content_length >= 1024 * 1024 * 50) break; // Limit to 50MB
            }
            fclose(fp);
            send(client_socket, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully.", strlen("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully."), 0);
        } else {
            send(client_socket, "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\nNot Found", strlen("HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\nNot Found"), 0);
        }
    }
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if (mkdir(UPLOAD_DIR, 0777) == -1 && errno != EEXIST) {
        perror("Failed to create uploads directory");
        exit(EXIT_FAILURE);
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        close(server_fd);
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

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}