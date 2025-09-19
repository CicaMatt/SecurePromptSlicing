#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define UPLOAD_DIR "./uploads/"
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;
    FILE *file = NULL;

    while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';
        if (strstr(buffer, "POST /upload HTTP/1.1")) {
            char *filename_start = strstr(buffer, "filename=\"") + strlen("filename=\"");
            char *filename_end = strchr(filename_start, '"');
            char filename[256];
            strncpy(filename, filename_start, filename_end - filename_start);
            filename[filename_end - filename_start] = '\0';

            file = fopen(strcat(UPLOAD_DIR, filename), "wb");
        } else if (strstr(buffer, "\r\n\r\n")) {
            buffer[strstr(buffer, "\r\n\r\n") - buffer + 4] = '\0';
            fwrite(&buffer[strstr(buffer, "\r\n\r\n") - buffer + 4], 1, bytes_read - (strstr(buffer, "\r\n\r\n") - buffer + 4), file);
        } else {
            if (file) {
                fwrite(buffer, 1, bytes_read, file);
            }
        }
    }

    if (file) fclose(file);
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    mkdir(UPLOAD_DIR, 0777);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
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
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}