#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int valread = read(client_socket, buffer, BUFFER_SIZE);
    if (valread <= 0) return;

    FILE *file;
    file = fopen("uploads/uploaded.pdf", "wb");
    if (!file) {
        perror("Failed to open file for writing");
        close(client_socket);
        return;
    }

    char *boundary_start = strstr(buffer, "boundary=");
    if (boundary_start == NULL) {
        fclose(file);
        close(client_socket);
        return;
    }
    boundary_start += strlen("boundary=");

    char *boundary_end = strchr(boundary_start, '\r');
    if (boundary_end == NULL) {
        fclose(file);
        close(client_socket);
        return;
    }

    char boundary[128];
    strncpy(boundary, boundary_start, boundary_end - boundary_start);
    boundary[boundary_end - boundary_start] = '\0';

    char *content_start = strstr(buffer, "\r\n\r\n");
    if (content_start == NULL) {
        fclose(file);
        close(client_socket);
        return;
    }
    content_start += 4;

    while (1) {
        fwrite(content_start, 1, valread - (content_start - buffer), file);

        int bytes_read = read(client_socket, buffer, BUFFER_SIZE);
        if (bytes_read <= 0) break;

        char *boundary_check = strstr(buffer, boundary);
        if (boundary_check != NULL) break;

        content_start = buffer;
    }

    fclose(file);
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    char *uploads_folder = "uploads";
    mkdir(uploads_folder, 0777);

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

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) > 0) {
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}