#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOAD_DIR "./uploads"

void save_file(char *filename, char *data) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("File opening failed");
        return;
    }
    fwrite(data, sizeof(char), strlen(data), file);
    fclose(file);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body>File uploaded successfully</body></html>";

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

        int valread = read(new_socket, buffer, BUFFER_SIZE);
        if (valread <= 0) {
            close(new_socket);
            continue;
        }

        char *boundary = "--";
        char *filename_start = strstr(buffer, "filename=\"") + strlen("filename=\"");
        char *filename_end = strchr(filename_start, '\"');
        int filename_len = filename_end - filename_start;
        char filename[filename_len + 1];
        strncpy(filename, filename_start, filename_len);
        filename[filename_len] = '\0';

        char *data_start = strstr(buffer, "\r\n\r\n") + strlen("\r\n\r\n");
        char *data_end = strstr(data_start, boundary) - strlen("\r\n");

        int data_len = data_end - data_start;
        char data[data_len + 1];
        strncpy(data, data_start, data_len);
        data[data_len] = '\0';

        char filepath[512];
        snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

        save_file(filepath, data);

        send(new_socket, hello, strlen(hello), 0);
        close(new_socket);
    }

    return 0;
}