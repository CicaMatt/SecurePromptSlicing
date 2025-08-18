#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void send_image(int client_socket, const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    struct stat st;
    stat(filename, &st);
    long size = st.st_size;

    char response[BUFFER_SIZE];
    snprintf(response, BUFFER_SIZE, "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\nContent-Type: image/jpeg\r\nConnection: close\r\n\r\n", size);
    send(client_socket, response, strlen(response), 0);

    char buffer[4096];
    ssize_t nread;
    while ((nread = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        send(client_socket, buffer, nread, 0);
    }

    fclose(file);
}

void handle_request(int client_socket, const char* request_path) {
    char image_path[256];
    snprintf(image_path, sizeof(image_path), "images%s", request_path);

    struct stat st;
    if (stat(image_path, &st) == 0 && S_ISREG(st.st_mode)) {
        send_image(client_socket, image_path);
    } else {
        const char* not_found = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
        send(client_socket, not_found, strlen(not_found), 0);
    }
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
        char buffer[BUFFER_SIZE] = {0};
        read(new_socket, buffer, BUFFER_SIZE);

        char* request_line = strtok(buffer, "\r\n");
        if (request_line != NULL) {
            char* method = strtok(request_line, " ");
            char* path = strtok(NULL, " ");

            if (strcmp(method, "GET") == 0) {
                handle_request(new_socket, path);
            }
        }

        close(new_socket);
    }

    return 0;
}