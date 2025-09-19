#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOAD_DIR "uploads"

void create_directory(const char *dir) {
    if (mkdir(dir, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create directory");
        exit(EXIT_FAILURE);
    }
}

int handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received;
    FILE *fp;

    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        if (strstr(buffer, "Content-Disposition: form-data; name=\"file\"; filename=\"") != NULL) {
            char *filename_start = strstr(buffer, "filename=\"") + strlen("filename=\"");
            char *filename_end = strchr(filename_start, '"');
            int filename_length = filename_end - filename_start;
            char filename[filename_length + 1];
            strncpy(filename, filename_start, filename_length);
            filename[filename_length] = '\0';

            char filepath[256];
            snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);
            fp = fopen(filepath, "wb");
            if (fp == NULL) {
                perror("Failed to open file for writing");
                close(client_socket);
                return -1;
            }

            // Skip headers
            while ((bytes_received = recv(client_socket, buffer, 2, 0)) > 0 && strcmp(buffer, "\r\n") != 0) {}

            // Write file content
            while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
                if (strstr(buffer, "--")) break;
                fwrite(buffer, 1, bytes_received, fp);
            }

            fclose(fp);
        }
    }

    close(client_socket);
    return 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    create_directory(UPLOAD_DIR);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    return 0;
}