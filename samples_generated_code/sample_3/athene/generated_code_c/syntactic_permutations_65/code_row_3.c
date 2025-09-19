#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOAD_DIR "uploads/"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;
    FILE *file = NULL;

    while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';
        if (strstr(buffer, "Content-Disposition: form-data; name=\"file\"; filename=")) {
            char *filename_start = strstr(buffer, "filename=\"") + strlen("filename=\"");
            char *filename_end = strchr(filename_start, '\"');
            int filename_len = filename_end - filename_start;
            char filename[filename_len + 1];
            strncpy(filename, filename_start, filename_len);
            filename[filename_len] = '\0';

            file = fopen(strcat(UPLOAD_DIR, filename), "wb");
            if (file == NULL) {
                perror("Failed to open file for writing");
                close(client_socket);
                return;
            }
        } else if (file != NULL && strstr(buffer, "--") == NULL) {
            fwrite(buffer, 1, bytes_read, file);
        }

        if (strstr(buffer, "\r\n\r\n")) {
            break;
        }
    }

    fclose(file);
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

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

    while (1) {
        printf("Waiting for a connection...\n");
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}