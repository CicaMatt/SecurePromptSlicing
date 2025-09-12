#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define PORT 8080
#define UPLOADS_DIR "uploads"
#define BUFFER_SIZE 1024

void create_uploads_directory() {
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0755);
    }
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    FILE *file;
    int bytes_received;

    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        if (strstr(buffer, "POST /upload") && strstr(buffer, "Content-Type: multipart/form-data")) {
            char filename[256];
            sscanf(buffer, "%*s; filename=\"%255[^\"]\"", filename);
            char filepath[512];
            snprintf(filepath, sizeof(filepath), "%s/%s", UPLOADS_DIR, filename);

            file = fopen(filepath, "wb");
            if (!file) {
                perror("Error opening file for writing");
                break;
            }

            char *data_start = strstr(buffer, "\r\n\r\n") + 4;
            int data_size = bytes_received - (data_start - buffer);
            fwrite(data_start, 1, data_size, file);

            while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
                if (strstr(buffer, "\r\n------")) break;
                fwrite(buffer, 1, bytes_received, file);
            }

            fclose(file);
        }
    }

    close(client_socket);
}

int main() {
    create_uploads_directory();

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
        handle_client(new_socket);
    }

    return 0;
}