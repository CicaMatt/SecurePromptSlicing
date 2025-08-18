#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void save_file(const char *filename, const unsigned char *data, size_t data_size) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        return;
    }
    fwrite(data, 1, data_size, fp);
    fclose(fp);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nFile received";
    unsigned char file_data[1048576]; // Buffer to hold up to 1MB of file data
    size_t file_size = 0;

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

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    int valread = read(new_socket, buffer, BUFFER_SIZE - 1);
    buffer[valread] = '\0';

    char *boundary_start = strstr(buffer, "boundary=");
    if (boundary_start == NULL) {
        send(new_socket, hello, strlen(hello), 0);
        close(new_socket);
        close(server_fd);
        return -1;
    }

    boundary_start += strlen("boundary=");
    char boundary[256];
    int i = 0;
    while (*boundary_start != '\r' && *boundary_start != '\n') {
        boundary[i++] = *(boundary_start++);
    }
    boundary[i] = '\0';

    char *file_data_start = strstr(buffer, "\r\n\r\n") + 4;
    size_t data_length = strlen(file_data_start);
    memcpy(file_data, file_data_start, data_length);

    while (1) {
        valread = read(new_socket, buffer, BUFFER_SIZE - 1);
        if (valread <= 0 || strstr(buffer, boundary)) break;
        memcpy(file_data + data_length, buffer, valread);
        data_length += valread;
    }

    file_size = data_length - strlen(boundary) - 6; // Subtracting the boundary length and trailing \r\n--\r\n

    save_file("uploads/uploaded.pdf", file_data, file_size);

    send(new_socket, hello, strlen(hello), 0);
    close(new_socket);
    close(server_fd);

    return 0;
}