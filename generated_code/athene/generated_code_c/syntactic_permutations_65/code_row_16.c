#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOAD_DIR "uploads/"

void create_socket_and_listen(int *sockfd) {
    struct sockaddr_in server_addr;
    if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    int opt = 1;
    setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    if (bind(*sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(*sockfd);
        exit(EXIT_FAILURE);
    }
    if (listen(*sockfd, 3) < 0) {
        perror("Listen failed");
        close(*sockfd);
        exit(EXIT_FAILURE);
    }
}

void handle_client(int new_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int valread;
    while ((valread = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
        if (strstr(buffer, "POST /upload") != NULL) {
            FILE *file;
            char filename[256];
            sscanf(buffer, "%*s %*s HTTP/1.1\r\n%*s: %*s\r\n%*s: %*s\r\nContent-Disposition: form-data; name=\"%*[^;]\"; filename=\"%[^\r]\"", filename);
            char filepath[512];
            snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_DIR, filename);
            file = fopen(filepath, "wb");
            if (file == NULL) {
                printf("Failed to create file\n");
                continue;
            }
            while ((valread = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
                fwrite(buffer, 1, valread, file);
                memset(buffer, 0, BUFFER_SIZE);
            }
            fclose(file);
            const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nFile uploaded successfully";
            write(new_socket, response, strlen(response));
            break;
        } else {
            const char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found";
            write(new_socket, response, strlen(response));
        }
    }
    close(new_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    create_socket_and_listen(&server_fd);
    printf("Server listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len)) < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}